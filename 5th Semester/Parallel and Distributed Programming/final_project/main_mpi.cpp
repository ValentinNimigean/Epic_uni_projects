#include <opencv2/opencv.hpp>
#include <mpi.h>
#include <iostream>
#include <vector>
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
    double x = 0;
    double y = 0;
    double scale = 1.0;
};

struct SearchTask {
    double scale;
    int startY;
    int endY;
};

Config loadConfig(const std::string& filename) {
    Config conf = {"scenes/scene.png", "templates/image.png", "scene1.png", false};
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
        } else if (key == "template_path") {
            conf.templatePath = "templates/" + value;
        } else if (key == "dynamic_stride") {
            conf.dynamicStride = (value == "true");
        }
    }
    return conf;
}

void convertToGray(const cv::Mat& input, cv::Mat& output) {
    cv::cvtColor(input, output, cv::COLOR_BGR2GRAY);
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

MatchResult searchSingleScale(const cv::Mat& sceneGray, const cv::Mat& templateGray, double scale, bool useDynamicStride) {
    MatchResult res;
    res.scale = scale;
    
    cv::Mat resized;
    cv::resize(templateGray, resized, cv::Size(), scale, scale, cv::INTER_NEAREST);
    
    int n = resized.rows * resized.cols;
    int maxX = sceneGray.cols - resized.cols;
    int maxY = sceneGray.rows - resized.rows;
    
    if (maxX < 0 || maxY < 0) return res;
    
    double sumT = 0, sumTT = 0;
    for (int y = 0; y < resized.rows; ++y) {
        const uchar* r = resized.ptr<uchar>(y);
        for (int x = 0; x < resized.cols; ++x) {
            double t = static_cast<double>(r[x]);
            sumT += t; sumTT += t * t;
        }
    }
    
    int stride = useDynamicStride ? std::max(2, sceneGray.cols / 100) : 2;
    
    for (int y = 0; y <= maxY; y += stride) {
        for (int x = 0; x <= maxX; x += stride) {
            double score = calculateNCC(sceneGray, resized, x, y, sumT, sumTT, n);
            if (score > res.score) {
                res.score = score;
                res.x = (double)x;
                res.y = (double)y;
            }
        }
    }
    return res;
}


int main(int argc, char** argv) {
    cv::setNumThreads(0); 
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    Config conf;
    char scenePathBuf[256];
    char templatePathBuf[256];
    char rawNameBuf[256];
    int strideFlag;
    if (world_rank == 0) {
        conf = loadConfig("config.txt");
        strncpy(scenePathBuf, conf.scenePath.c_str(), 255);
        strncpy(templatePathBuf, conf.templatePath.c_str(), 255);
        strncpy(rawNameBuf, conf.rawSceneName.c_str(), 255);
        strideFlag = conf.dynamicStride ? 1 : 0;
        
        std::cout << "MPI Master (Rank 0) starting with " << world_size << " processes." << std::endl;
        std::cout << "Target: " << conf.scenePath << std::endl;
    }
-
    MPI_Bcast(scenePathBuf, 256, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(templatePathBuf, 256, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(rawNameBuf, 256, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(&strideFlag, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (world_rank != 0) {
        conf.scenePath = std::string(scenePathBuf);
        conf.templatePath = std::string(templatePathBuf);
        conf.rawSceneName = std::string(rawNameBuf);
        conf.dynamicStride = (strideFlag == 1);
    }

    cv::Mat sceneColor = cv::imread(conf.scenePath);
    cv::Mat templateColor = cv::imread(conf.templatePath);

    if (sceneColor.empty() || templateColor.empty()) {
        if (world_rank == 0) std::cerr << "Error loading images on Rank " << world_rank << std::endl;
        MPI_Finalize();
        return -1;
    }

    MPI_Barrier(MPI_COMM_WORLD); 
    double startTime = MPI_Wtime();

    cv::Mat sceneGray, templateGray;
    convertToGray(sceneColor, sceneGray);
    convertToGray(templateColor, templateGray);

    std::vector<double> allScales;
    for (double s = 0.1; s <= 2.0; s += 0.1) {
        allScales.push_back(s);
    }
    MatchResult localBest;
    
    for (size_t i = world_rank; i < allScales.size(); i += world_size) {
        double currentScale = allScales[i];
        MatchResult r = searchSingleScale(sceneGray, templateGray, currentScale, conf.dynamicStride);
        if (r.score > localBest.score) {
            localBest = r;
        }
    }

    double localData[6] = { localBest.score, localBest.x, localBest.y, localBest.scale };
    std::vector<double> gatheredData;

    if (world_rank == 0) {
        gatheredData.resize(6 * world_size);
    }

    MPI_Gather(localData, 6, MPI_DOUBLE, 
               gatheredData.data(), 6, MPI_DOUBLE, 
               0, MPI_COMM_WORLD);
    double endTime = MPI_Wtime();
    double durationMs = (endTime - startTime) * 1000.0;
    if (world_rank == 0) {
        MatchResult globalBest;
        for (int i = 0; i < world_size; ++i) {
            double score = gatheredData[i*6 + 0];
            if (score > globalBest.score) {
                globalBest.score = score;
                globalBest.x     = gatheredData[i*6 + 1];
                globalBest.y     = gatheredData[i*6 + 2];
                globalBest.scale = gatheredData[i*6 + 3];
            }
        }

        int foundW = static_cast<int>(templateColor.cols * globalBest.scale);
        int foundH = static_cast<int>(templateColor.rows * globalBest.scale);
        cv::Point loc(static_cast<int>(globalBest.x), static_cast<int>(globalBest.y));
        
        cv::Mat sceneResult = sceneColor.clone();
        if (globalBest.score > 0) {
            cv::rectangle(sceneResult, loc, cv::Point(loc.x + foundW, loc.y + foundH), cv::Scalar(0, 255, 0), 3);
            cv::putText(sceneResult, "Time: " + std::to_string((long long)durationMs) + " ms", cv::Point(20, 40), 0, 0.8, {0, 0, 255}, 2);
            cv::putText(sceneResult, "Score: " + std::to_string(globalBest.score).substr(0, 5), cv::Point(20, 80), 0, 0.8, {0, 0, 255}, 2);
        }

        int stripHeight = 200; 
        cv::Mat footer = cv::Mat::zeros(cv::Size(sceneColor.cols, stripHeight), sceneColor.type());
        
        cv::Mat templateDisplay;
        double templateAspect = static_cast<double>(templateColor.cols) / templateColor.rows;
        int tW = static_cast<int>((stripHeight - 40) * templateAspect);
        cv::resize(templateColor, templateDisplay, cv::Size(tW, stripHeight - 40));
        cv::putText(footer, "TEMPLATE", cv::Point(20, 25), 0, 0.6, {255, 255, 255}, 1);
        templateDisplay.copyTo(footer(cv::Rect(20, 35, templateDisplay.cols, templateDisplay.rows)));

        if (globalBest.score > 0) {
            cv::Rect roi(loc.x, loc.y, foundW, foundH);
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
        }

        std::string outputFilename = "results/result_" + conf.rawSceneName;
        cv::imwrite(outputFilename, canvas);
        std::cout << "Result saved to: " << outputFilename << std::endl;

        std::ofstream logFile("log.txt", std::ios::app);
        if (logFile.is_open()) {
            logFile << "Technology: MPI (" << world_size << " processes) | " 
                    << "Accuracy: " << std::fixed << std::setprecision(5) << globalBest.score << " | "
                    << "Time: " << (long long)durationMs << " ms" << std::endl;
        }

      
    }

    MPI_Finalize();
    return 0;
}