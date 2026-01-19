#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <future>
#include <chrono>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include <filesystem> 
#include <iomanip> 

namespace fs = std::filesystem;

struct Config {
    std::string scenePath;
    std::string templatePath;
    std::string rawSceneName; 
    bool dynamicStride;
};

struct MatchResult {
    double score = -1.0;
    cv::Point location = cv::Point(0, 0);
    double scale = 1.0;
};

struct SearchTask {
    double scale;
    int startY;
    int endY;
    bool useDynamicStride;
};

Config loadConfig(const std::string& filename) {
    Config conf = {"scenes/scene1.png", "templates/image.png", "scene1.png", false};
    
    std::ifstream file(filename);
    if (!file.is_open()) return conf;
    
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
        
        if (key == "scene_path") {
            conf.rawSceneName = value;
            conf.scenePath = "scenes/" + value; 
        }
        else if (key == "template_path") {
            conf.templatePath = "templates/" + value;
        }
        else if (key == "dynamic_stride") {
            conf.dynamicStride = (value == "true");
        }
    }
    return conf;
}

void grayscaleStrip(const cv::Mat& input, cv::Mat& output, int startY, int endY) {
    for (int y = startY; y < endY; ++y) {
        const cv::Vec3b* pixelBGR = input.ptr<cv::Vec3b>(y);
        uchar* pixelGray = output.ptr<uchar>(y);
        for (int x = 0; x < input.cols; ++x) {
            pixelGray[x] = static_cast<uchar>(0.299 * pixelBGR[x][2] + 0.587 * pixelBGR[x][1] + 0.114 * pixelBGR[x][0]);
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
        futures.push_back(std::async(std::launch::async, grayscaleStrip, std::ref(input), std::ref(output), startY, endY));
    }
    for (auto& f : futures) f.get();
}

double calculateNCC(const cv::Mat& scene, const cv::Mat& temp, int startX, int startY, double sumT, double sumTT, int n) {
    double sumF = 0, sumFF = 0, sumFT = 0;
    
    for (int y = 0; y < temp.rows; ++y) {
        const uchar* sRow = scene.ptr<uchar>(startY + y) + startX;
        const uchar* tRow = temp.ptr<uchar>(y);
        
        for (int x = 0; x < temp.cols; ++x) {
            double f = static_cast<double>(sRow[x]);
            double t = static_cast<double>(tRow[x]);
            sumF += f; sumFF += f * f; sumFT += f * t;
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
            sumT += t; sumTT += t * t;
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
    
    std::cout << "Loading Scene: " << conf.scenePath << std::endl;
    std::cout << "Loading Template: " << conf.templatePath << std::endl;

    cv::Mat sceneColor = cv::imread(conf.scenePath);
    cv::Mat templateColor = cv::imread(conf.templatePath);

    if (sceneColor.empty() || templateColor.empty()) {
        std::cout << "Error loading images. Check 'scenes' and 'templates' folders." << std::endl;
        return -1;
    }

    auto start = std::chrono::high_resolution_clock::now();
    
    cv::Mat sceneGray, templateGray;
    parallelGrayscale(sceneColor, sceneGray);
    parallelGrayscale(templateColor, templateGray);

    std::vector<SearchTask> taskList;
    int segmentsPerScale = std::thread::hardware_concurrency(); 
    
    for (double s = 0.3; s <= 2.0; s += 0.1) {
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
    long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    int foundW = static_cast<int>(templateColor.cols * best.scale);
    int foundH = static_cast<int>(templateColor.rows * best.scale);
    cv::Mat sceneResult = sceneColor.clone();

    if (best.score > 0) {
        cv::rectangle(sceneResult, best.location, cv::Point(best.location.x + foundW, best.location.y + foundH), cv::Scalar(0, 255, 0), 3);
        cv::putText(sceneResult, "Time: " + std::to_string(duration) + " ms", cv::Point(20, 40), 0, 0.8, {0, 0, 255}, 2);
        cv::putText(sceneResult, "Score: " + std::to_string(best.score).substr(0, 5), cv::Point(20, 80), 0, 0.8, {0, 0, 255}, 2);
    }

    int stripHeight = 200; 
    cv::Mat footer = cv::Mat::zeros(cv::Size(sceneColor.cols, stripHeight), sceneColor.type());
    
    cv::Mat templateDisplay;
    double templateAspect = static_cast<double>(templateColor.cols) / templateColor.rows;
    int tW = static_cast<int>((stripHeight - 40) * templateAspect);
    cv::resize(templateColor, templateDisplay, cv::Size(tW, stripHeight - 40));
    
    cv::putText(footer, "TEMPLATE", cv::Point(20, 25), 0, 0.6, {255, 255, 255}, 1);
    templateDisplay.copyTo(footer(cv::Rect(20, 35, templateDisplay.cols, templateDisplay.rows)));

    if (best.score > 0) {
        cv::Rect roi(best.location.x, best.location.y, foundW, foundH);
        roi &= cv::Rect(0, 0, sceneColor.cols, sceneColor.rows);
        
        if (roi.width > 0 && roi.height > 0) {
            cv::Mat foundCrop = sceneColor(roi);
            cv::Mat foundDisplay;
            
            double foundAspect = static_cast<double>(foundCrop.cols) / foundCrop.rows;
            int fW = static_cast<int>((stripHeight - 40) * foundAspect);
            cv::resize(foundCrop, foundDisplay, cv::Size(fW, stripHeight - 40));

            int startX = tW + 100;
            if (startX + fW < footer.cols) {
                cv::putText(footer, "FOUND MATCH", cv::Point(startX, 25), 0, 0.6, {0, 255, 0}, 1);
                foundDisplay.copyTo(footer(cv::Rect(startX, 35, foundDisplay.cols, foundDisplay.rows)));
            }
        }
    }

    cv::Mat canvas;
    cv::vconcat(sceneResult, footer, canvas);

 
    if (!fs::exists("results")) {
        fs::create_directory("results");
        std::cout << "Created 'results' directory." << std::endl;
    }

    std::string outputFilename = "results/result_" + conf.rawSceneName;
    cv::imwrite(outputFilename, canvas);
    std::cout << "Result saved to: " << outputFilename << std::endl;

    std::ofstream logFile("log.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << "Technology: Threads | " 
                << "Accuracy: " << std::fixed << std::setprecision(5) << best.score << " | "
                << "Time: " << duration << " ms" << std::endl;
        std::cout << "Data appended to log.txt" << std::endl;
    } else {
        std::cerr << "Could not open log.txt for writing." << std::endl;
    }

  

    return 0;
}