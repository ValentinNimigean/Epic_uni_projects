#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <random>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>

class BoundedQueue {
public:
    explicit BoundedQueue(size_t maxSize) : maxSize(maxSize), finished(false) {}

    void enqueue(double value) {
        std::unique_lock<std::mutex> lock(mtx);
        notFull.wait(lock, [this]() { return queue.size() < maxSize || finished; });
        if (finished) return;
        queue.push(value);
        notEmpty.notify_one();
    }

    bool dequeue(double& value) {
        std::unique_lock<std::mutex> lock(mtx);
        notEmpty.wait(lock, [this]() { return !queue.empty() || finished; });
        if (queue.empty() && finished)
            return false; 
        value = queue.front();
        queue.pop();
        notFull.notify_one();
        return true;
    }

    void close() {
        std::unique_lock<std::mutex> lock(mtx);
        finished = true;
        notEmpty.notify_all();
        notFull.notify_all();
    }

private:
    std::mutex mtx;
    std::condition_variable notFull;
    std::condition_variable notEmpty;
    std::queue<double> queue;
    size_t maxSize;
    bool finished;
};

void producer(const std::vector<double>& A,
              const std::vector<double>& B,
              BoundedQueue& queue)
{
    for (size_t i = 0; i < A.size(); ++i) {
        double product = A[i] * B[i];
        queue.enqueue(product);
    }
    queue.close();
}

void consumer(BoundedQueue& queue, double& result)
{
    result = 0.0;
    double value;
    while (queue.dequeue(value)) {
        result += value;
    }
}

std::string currentTimeString() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* local_tm = std::localtime(&now_c);
    std::ostringstream oss;
    oss << std::put_time(local_tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

int main() {
    std::ofstream logFile("log.txt", std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Error: Could not open log.txt for writing.\n";
        return 1;
    }

    std::cout << "=== Scalar Product (Producer-Consumer, Two Threads) ===\n";
    std::cout << "Type 'stop' at any time to quit.\n\n";

    std::string input;

    while (true) {
        std::cout << "Enter vector size (or 'stop'): ";
        std::cin >> input;
        if (input == "stop") break;
        size_t vectorSize = std::stoull(input);

        std::cout << "Enter max random value: ";
        std::cin >> input;
        if (input == "stop") break;
        double maxVal = std::stod(input);

        std::cout << "Enter queue size: ";
        std::cin >> input;
        if (input == "stop") break;
        size_t queueSize = std::stoull(input);

        std::vector<double> A(vectorSize);
        std::vector<double> B(vectorSize);
        std::mt19937 rng(42);
        std::uniform_real_distribution<double> dist(0.0, maxVal);

        for (size_t i = 0; i < vectorSize; ++i) {
            A[i] = dist(rng);
            B[i] = dist(rng);
        }

        BoundedQueue queue(queueSize);
        double result = 0.0;

        auto start = std::chrono::high_resolution_clock::now();

        std::thread prodThread(producer, std::cref(A), std::cref(B), std::ref(queue));
        std::thread consThread(consumer, std::ref(queue), std::ref(result));

        prodThread.join();
        consThread.join();

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << "Result: " << result << "\n";
        std::cout << "Time: " << elapsed << " ms\n";
        std::cout << "--------------------------------------------\n";

        logFile << "[" << currentTimeString() << "] "
                << "VectorSize=" << vectorSize
                << ", MaxVal=" << maxVal
                << ", QueueSize=" << queueSize
                << ", Result=" << result
                << ", Time=" << elapsed << " ms\n";
        logFile.flush();
    }

    std::cout << "\nProgram stopped. Results saved to log.txt ✅\n";
    logFile.close();
    return 0;
}