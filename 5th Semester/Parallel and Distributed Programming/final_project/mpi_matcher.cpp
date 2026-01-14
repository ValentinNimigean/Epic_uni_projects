#include <mpi.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <algorithm>

// ---------------- STRUCTS ----------------

struct MatchResult {
    double score = -1.0;
    int x = 0;
    int y = 0;
    double scale = 1.0;
};

struct SearchTask {
    double scale;
    int startY;
    int endY;
    bool dynamicStride;
};

// ---------------- UTILS ----------------

void broadcastMat(cv::Mat& mat, int rank) {
    int meta[3];
    if (rank == 0) {
        meta[0] = mat.rows;
        meta[1] = mat.cols;
        meta[2] = mat.type();
    }
    MPI_Bcast(meta, 3, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank != 0) mat.create(meta[0], meta[1], meta[2]);
    MPI_Bcast(mat.data, mat.total() * mat.elemSize(), MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
}

double calculateNCC(const cv::Mat& scene, const cv::Mat& temp,
                    int startX, int startY,
                    double sumT, double sumTT, int n) {
    double sumF = 0, sumFF = 0, sumFT = 0;

    for (int y = 0; y < temp.rows; ++y) {
        const uchar* s = scene.ptr<uchar>(startY + y) + startX;
        const uchar* t = temp.ptr<uchar>(y);
        for (int x = 0; x < temp.cols; ++x) {
            double fv = s[x];
            double tv = t[x];
            sumF += fv;
            sumFF += fv * fv;
            sumFT += fv * tv;
        }
    }

    double num = n * sumFT - sumF * sumT;
    double den = std::sqrt((n * sumFF - sumF * sumF) *
                           (n * sumTT - sumT * sumT));
    return (den < 1e-6) ? 0.0 : num / den;
}

// ---------------- MAIN ----------------

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    cv::Mat sceneGray, templateGray, sceneColor;

    // -------- Rank 0 loads images --------
    if (rank == 0) {
        sceneColor = cv::imread("scene1.png");
        cv::Mat templateColor = cv::imread("image.png");

        if (sceneColor.empty() || templateColor.empty()) {
            std::cerr << "Image load failed\n";
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        cv::cvtColor(sceneColor, sceneGray, cv::COLOR_BGR2GRAY);
        cv::cvtColor(templateColor, templateGray, cv::COLOR_BGR2GRAY);
    }

    broadcastMat(sceneGray, rank);
    broadcastMat(templateGray, rank);

    auto start = std::chrono::high_resolution_clock::now();

    // -------- BUILD TASK LIST (Rank 0) --------
    std::vector<SearchTask> tasks;
    if (rank == 0) {
        int segments = size * 2; // important: more tasks than ranks

        for (double s = 0.3; s <= 2.0; s += 0.1) {
            int scaledH = int(templateGray.rows * s);
            int scaledW = int(templateGray.cols * s);
            if (scaledH >= sceneGray.rows || scaledW >= sceneGray.cols)
                continue;

            int maxY = sceneGray.rows - scaledH;
            int strip = maxY / segments;

            for (int i = 0; i < segments; ++i) {
                int y0 = i * strip;
                int y1 = (i == segments - 1) ? maxY : y0 + strip;
                tasks.push_back({s, y0, y1, false});
            }
        }
    }

    // -------- Broadcast task count --------
    int taskCount = tasks.size();
    MPI_Bcast(&taskCount, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank != 0) tasks.resize(taskCount);
    MPI_Bcast(tasks.data(), taskCount * sizeof(SearchTask),
              MPI_BYTE, 0, MPI_COMM_WORLD);

    // -------- EXECUTE TASKS --------
    MatchResult localBest;

    for (int i = rank; i < taskCount; i += size) {
        const SearchTask& t = tasks[i];

        cv::Mat resized;
        cv::resize(templateGray, resized, cv::Size(), t.scale, t.scale,
                   cv::INTER_NEAREST);

        int maxX = sceneGray.cols - resized.cols;
        if (maxX < 0) continue;

        double sumT = 0, sumTT = 0;
        for (int y = 0; y < resized.rows; ++y) {
            const uchar* r = resized.ptr<uchar>(y);
            for (int x = 0; x < resized.cols; ++x) {
                sumT += r[x];
                sumTT += r[x] * r[x];
            }
        }

        int n = resized.rows * resized.cols;
        int stride = 2;

        for (int y = t.startY; y < t.endY; y += stride) {
            for (int x = 0; x <= maxX; x += stride) {
                double score = calculateNCC(sceneGray, resized, x, y,
                                            sumT, sumTT, n);
                if (score > localBest.score) {
                    localBest = {score, x, y, t.scale};
                }
            }
        }
    }

    // -------- REDUCE BEST RESULT --------
    struct {
        double score;
        int rank;
    } in{localBest.score, rank}, out;

    MPI_Allreduce(&in, &out, 1, MPI_DOUBLE_INT, MPI_MAXLOC, MPI_COMM_WORLD);

    MatchResult globalBest;
    if (rank == out.rank) globalBest = localBest;

    MPI_Bcast(&globalBest, sizeof(MatchResult),
              MPI_BYTE, out.rank, MPI_COMM_WORLD);

    // -------- DISPLAY --------
    if (rank == 0) {
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Time: "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
                  << " ms\n";

        int w = int(templateGray.cols * globalBest.scale);
        int h = int(templateGray.rows * globalBest.scale);

        cv::rectangle(sceneColor,
                      {globalBest.x, globalBest.y},
                      {globalBest.x + w, globalBest.y + h},
                      {0, 255, 0}, 3);

        cv::imshow("MPI Task-Based Result", sceneColor);
        cv::waitKey(0);
    }

    MPI_Finalize();
    return 0;
}
