#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudawarping.hpp>
#include <opencv2/cudaarithm.hpp>
#include <iostream>
#include <vector>
#include <chrono>

struct Config {
    std::string scenePath;
    std::string templatePath;
};

struct MatchResult {
    double score = -1.0;
    cv::Point location = cv::Point(0, 0);
    double scale = 1.0;
};

int main() {
    // 1. Setup and Load Images
    Config conf = {"scene1.png", "image.png"};
    cv::Mat h_scene = cv::imread(conf.scenePath);
    cv::Mat h_template = cv::imread(conf.templatePath);

    if (h_scene.empty() || h_template.empty()) {
        std::cerr << "Error loading images!" << std::endl;
        return -1;
    }

    auto start = std::chrono::high_resolution_clock::now();

    // 2. Upload to GPU Memory
    cv::cuda::GpuMat d_scene, d_template, d_sceneGray, d_templateGray;
    d_scene.upload(h_scene);
    d_template.upload(h_template);

    // 3. Parallel Grayscale Conversion (on GPU)
    cv::cuda::cvtColor(d_scene, d_sceneGray, cv::COLOR_BGR2GRAY);
    cv::cuda::cvtColor(d_template, d_templateGray, cv::COLOR_BGR2GRAY);

    MatchResult best;
    
    // 4. Multi-Scale Search on GPU
    // Instead of manual loops, we use CUDA-optimized matchers
    cv::Ptr<cv::cuda::TemplateMatching> matcher = 
        cv::cuda::createTemplateMatching(CV_8UC1, cv::TM_CCOEFF_NORMED);

    for (double s = 0.3; s <= 2.0; s += 0.1) {
        cv::cuda::GpuMat d_resized, d_result;
        
        // GPU Resizing
        int newW = static_cast<int>(d_templateGray.cols * s);
        int newH = static_cast<int>(d_templateGray.rows * s);
        
        // Boundary check
        if (newW >= d_sceneGray.cols || newH >= d_sceneGray.rows) continue;
        
        cv::cuda::resize(d_templateGray, d_resized, cv::Size(newW, newH), 0, 0, cv::INTER_NEAREST);

        // GPU Template Matching (Equivalent to your parallel manual NCC)
        matcher->match(d_sceneGray, d_resized, d_result);

        // Find best score for this scale
        double minVal, maxVal;
        cv::Point minLoc, maxLoc;
        cv::cuda::minMaxLoc(d_result, &minVal, &maxVal, &minLoc, &maxLoc);

        if (maxVal > best.score) {
            best.score = maxVal;
            best.location = maxLoc;
            best.scale = s;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // 5. Visualize Results (Same UI Logic)
    if (best.score > 0) {
        int w = static_cast<int>(h_template.cols * best.scale);
        int h = static_cast<int>(h_template.rows * best.scale);
        cv::rectangle(h_scene, best.location, cv::Point(best.location.x + w, best.location.y + h), cv::Scalar(0, 255, 0), 3);
        
        cv::putText(h_scene, "GPU Time: " + std::to_string(duration) + " ms", cv::Point(20, 40), 0, 0.8, {0,0,255}, 2);
        cv::putText(h_scene, "Score: " + std::to_string(best.score).substr(0, 5), cv::Point(20, 80), 0, 0.8, {0,0,255}, 2);
    }

    // Composite Window
    cv::Mat footer = cv::Mat::zeros(cv::Size(h_scene.cols, 150), h_scene.type());
    cv::Mat resizedTemp;
    double aspect = static_cast<double>(h_template.rows) / h_template.cols;
    cv::resize(h_template, resizedTemp, cv::Size(static_cast<int>(150/aspect), 150));
    resizedTemp.copyTo(footer(cv::Rect((footer.cols - resizedTemp.cols)/2, 0, resizedTemp.cols, 150)));

    cv::Mat canvas;
    cv::vconcat(h_scene, footer, canvas);
    cv::imshow("GPU Detection Results", canvas);
    cv::waitKey(0);

    return 0;
}