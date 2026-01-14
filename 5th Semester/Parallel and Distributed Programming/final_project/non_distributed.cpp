#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <future>
#include <chrono>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>

// Structure to store configuration settings
struct Config {
    std::string scenePath;
    std::string templatePath;
    bool dynamicStride;
};

// Structure to store match results
struct MatchResult {
    double score = -1.0;
    cv::Point location = cv::Point(0, 0);
    double scale = 1.0;
};

// Structure to define a specific search task
struct SearchTask {
    double scale;
    int startY;
    int endY;
    bool useDynamicStride;
};

// --- ROBUST CONFIG PARSER ---
// Trims carriage returns and spaces to prevent imread errors
Config loadConfig(const std::string& filename) {
    Config conf = {"scene1.png", "image.png", false};
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Warning: config.txt not found, using defaults." << std::endl;
        return conf;
    }
    std::string line;
    while (std::getline(file, line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
        size_t colonPos = line.find(":");
        if (colonPos == std::string::npos) continue;

        std::string key = line.substr(0, colonPos);
        std::string value = line.substr(colonPos + 1);
        value.erase(0, value.find_first_not_of(" ")); 
        value.erase(value.find_last_not_of(" ") + 1); 

        if (key == "scene_path") conf.scenePath = value;
        else if (key == "template_path") conf.templatePath = value;
        else if (key == "dynamic_stride") conf.dynamicStride = (value == "true");
    }
    return conf;
}

void grayscaleStrip(const cv::Mat& input, cv::Mat& output, int startY, int endY) {
    for (int y = startY; y < endY; ++y) {
        const cv::Vec3b* pixelBGR = input.ptr<cv::Vec3b>(y);
        uchar* pixelGray = output.ptr<uchar>(y);
        for (int x = 0; x < input.cols; ++x) {
            pixelGray[x] = static_cast<uchar>(0.299 * pixelBGR[x][2] + 
                                              0.587 * pixelBGR[x][1] + 
                                              0.114 * pixelBGR[x][0]);
        }
    }
}

void parallelGrayscale(const cv::Mat& input, cv::Mat& output) {
    output.create(input.rows, input.cols, CV_8UC1);
    int numThreads = std::thread::hardware_concurrency();
    int stripHeight = input.rows / numThreads;
    std::vector<std::future<void>> futures;

    for (int i = 0; i < numThreads; ++i) {
        int startY = i * stripHeight;
        int endY = (i == numThreads - 1) ? input.rows : startY + stripHeight;
        futures.push_back(std::async(std::launch::async, grayscaleStrip, 
                                     std::ref(input), std::ref(output), startY, endY));
    }
    for (auto& f : futures) f.get();
}
double calculateNCC(const cv::Mat& scene, const cv::Mat& temp, int startX, int startY, 
                    double sumT, double sumTT, int n) {
    double sumF = 0, sumFF = 0, sumFT = 0;

    for (int y = 0; y < temp.rows; ++y) {
        const uchar* sRow = scene.ptr<uchar>(startY + y) + startX;
        const uchar* tRow = temp.ptr<uchar>(y);
        for (int x = 0; x < temp.cols; ++x) {
            double f = static_cast<double>(sRow[x]);
            double t = static_cast<double>(tRow[x]);
            sumF += f;
            sumFF += f * f;
            sumFT += f * t;
        }
    }
    double num = n * sumFT - sumF * sumT;
    double den = std::sqrt((n * sumFF - sumF * sumF) * (n * sumTT - sumT * sumT));
    return (den <= 1e-6) ? 0 : num / den;
}

MatchResult executeSearch(cv::Mat sceneGray, cv::Mat templateGray, SearchTask task) {
    MatchResult res;
    res.scale = task.scale;
    
    cv::Mat resized;
    cv::resize(templateGray, resized, cv::Size(), task.scale, task.scale, cv::INTER_NEAREST);

    int n = resized.rows * resized.cols;
    int maxX = sceneGray.cols - resized.cols;
    if (maxX < 0) return res;

    double sumT = 0, sumTT = 0;
    for (int y = 0; y < resized.rows; ++y) {
        const uchar* r = resized.ptr<uchar>(y);
        for (int x = 0; x < resized.cols; ++x) {
            double t = static_cast<double>(r[x]);
            sumT += t;
            sumTT += t * t;
        }
    }

    int stride = task.useDynamicStride ? std::max(2, sceneGray.cols / 100) : 2; 

    for (int y = task.startY; y < task.endY; y += stride) {
        for (int x = 0; x <= maxX; x += stride) {
            double score = calculateNCC(sceneGray, resized, x, y, sumT, sumTT, n);
            if (score > res.score) {
                res.score = score;
                res.location = cv::Point(x, y);
            }
        }
    }
    return res;
}
int main() {
    Config conf = loadConfig("config.txt");
    cv::Mat sceneColor = cv::imread(conf.scenePath);
    cv::Mat templateColor = cv::imread(conf.templatePath);

    if (sceneColor.empty() || templateColor.empty()) {
        std::cout << "Error loading images from config paths: " << conf.scenePath << ", " << conf.templatePath << std::endl;
        return -1;
    }

    auto start = std::chrono::high_resolution_clock::now();

    cv::Mat sceneGray, templateGray;
    parallelGrayscale(sceneColor, sceneGray);
    parallelGrayscale(templateColor, templateGray);

    std::vector<SearchTask> taskList;
    int segmentsPerScale = std::thread::hardware_concurrency(); 

    for (double s = 0.1; s <= 2.0; s += 0.1) {
        int scaledH = static_cast<int>(templateGray.rows * s);
        int scaledW = static_cast<int>(templateGray.cols * s);
        if (scaledH >= sceneGray.rows || scaledW >= sceneGray.cols) continue;

        int totalSearchHeight = sceneGray.rows - scaledH;
        int stripHeight = totalSearchHeight / segmentsPerScale;

        for (int i = 0; i < segmentsPerScale; ++i) {
            int startY = i * stripHeight;
            int endY = (i == segmentsPerScale - 1) ? totalSearchHeight : startY + stripHeight;
            taskList.push_back({s, startY, endY, conf.dynamicStride});
        }
    }

    std::vector<std::future<MatchResult>> futures;
    for (const auto& task : taskList) {
        futures.push_back(std::async(std::launch::async, executeSearch, sceneGray, templateGray, task));
    }

    MatchResult best;
    for (auto& f : futures) {
        MatchResult r = f.get();
        if (r.score > best.score) best = r;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // Draw result on sceneColor
    if (best.score > 0) {
        int w = static_cast<int>(templateGray.cols * best.scale);
        int h = static_cast<int>(templateGray.rows * best.scale);
        cv::rectangle(sceneColor, best.location, cv::Point(best.location.x + w, best.location.y + h), cv::Scalar(0, 255, 0), 3);

        cv::putText(sceneColor, "Time: " + std::to_string(duration) + " ms", cv::Point(20, 40), 0, 0.8, {0, 0, 255}, 2);
        cv::putText(sceneColor, "Score: " + std::to_string(best.score).substr(0, 5), cv::Point(20, 80), 0, 0.8, {0, 0, 255}, 2);
        cv::putText(sceneColor, "Scale: " + std::to_string(best.scale).substr(0, 3), cv::Point(20, 120), 0, 0.8, {0, 0, 255}, 2);
    }

    // --- NEW: Create Composite Window Layout ---
    
    // 1. Prepare the template strip
    cv::Mat templateStrip;
    double aspectRatio = static_cast<double>(templateColor.rows) / templateColor.cols;
    int targetHeight = 150; // Set how tall you want the template bar to be
    int targetWidth = sceneColor.cols;
    
    // Create a black background for the bottom strip
    templateStrip = cv::Mat::zeros(cv::Size(targetWidth, targetHeight), sceneColor.type());
    
    // Resize template to fit inside the bottom strip height (maintaining aspect ratio)
    cv::Mat resizedTemplate;
    int displayW = static_cast<int>(targetHeight / aspectRatio);
    cv::resize(templateColor, resizedTemplate, cv::Size(displayW, targetHeight));
    
    // Place the template in the middle of the bottom strip
    int xOffset = (targetWidth - displayW) / 2;
    resizedTemplate.copyTo(templateStrip(cv::Rect(xOffset, 0, displayW, targetHeight)));
    
    // Label the template strip
    cv::putText(templateStrip, "SEARCH TEMPLATE", cv::Point(10, 30), 0, 0.6, {255, 255, 255}, 1);

    // 2. Vertical Concatenation
    cv::Mat canvas;
    cv::vconcat(sceneColor, templateStrip, canvas);

    // --- Display ---
    cv::namedWindow("Detection Results", cv::WINDOW_NORMAL);
    cv::imshow("Detection Results", canvas);
    
    while (true) {
        if (cv::waitKey(30) == 27) break; 
    }
    cv::destroyAllWindows();

    return 0;
}