#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <mutex>
#include <cstdlib>
using namespace std;

using Matrix = vector<vector<double>>;

mutex log_mutex; 
ofstream logFile;
bool enableLogging = true;

void logMessage(const string &msg) {
    if (!enableLogging) return;
    lock_guard<mutex> lock(log_mutex);
    logFile << msg << flush;
}

double computeElement(const Matrix &A, const Matrix &B, int row, int col, int thread_id) {
    int n = A[0].size();
    double sum = 0.0;
    for (int k = 0; k < n; ++k)
        sum += A[row][k] * B[k][col];

    if (enableLogging) {
        stringstream ss;
        ss << "Thread " << thread_id << " computed C(" << row << "," << col << ") = " << sum << "\n";
        cout << "Thread " << thread_id << " computed C(" << row << "," << col << ") = " << sum << "\n";
        logMessage(ss.str());
    }

    return sum;
}

void threadWorker_rowMajor(const Matrix &A, const Matrix &B, Matrix &C, int thread_id, int num_threads) {
    int n = C.size();
    int totalElements = n * n;
    int base = totalElements / num_threads;
    int remainder = totalElements % num_threads;
    int start = thread_id * base;
    int end = start + base;
    if (thread_id == num_threads - 1) end += remainder;

    for (int idx = start; idx < end; ++idx) {
        int row = idx / n;
        int col = idx % n;
        C[row][col] = computeElement(A, B, row, col, thread_id);
    }
}

void threadWorker_colMajor(const Matrix &A, const Matrix &B, Matrix &C, int thread_id, int num_threads) {
    int n = C.size();
    int totalElements = n * n;
    int base = totalElements / num_threads;
    int remainder = totalElements % num_threads;
    int start = thread_id * base;
    int end = start + base;
    if (thread_id == num_threads - 1) end += remainder;

    for (int idx = start; idx < end; ++idx) {
        int col = idx / n;
        int row = idx % n;
        C[row][col] = computeElement(A, B, row, col, thread_id);
    }
}

void threadWorker_everyK(const Matrix &A, const Matrix &B, Matrix &C, int thread_id, int num_threads) {
    int n = C.size();
    for (int idx = thread_id; idx < n * n; idx += num_threads) {
        int row = idx / n;
        int col = idx % n;
        C[row][col] = computeElement(A, B, row, col, thread_id);
    }
}

void multiply(const Matrix &A, const Matrix &B, Matrix &C, int num_threads, int method) {
    vector<thread> threads;
    auto start_time = chrono::high_resolution_clock::now();

    for (int t = 0; t < num_threads; ++t) {
        if (method == 1)
            threads.emplace_back(threadWorker_rowMajor, cref(A), cref(B), ref(C), t, num_threads);
        else if (method == 2)
            threads.emplace_back(threadWorker_colMajor, cref(A), cref(B), ref(C), t, num_threads);
        else
            threads.emplace_back(threadWorker_everyK, cref(A), cref(B), ref(C), t, num_threads);
    }

    for (auto &th : threads) th.join();

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end_time - start_time;

    if (enableLogging) {
        logFile << "\n=== Summary ===\n";
        logFile << "Method: " << method
                << "\nThreads: " << num_threads
                << "\nMatrix size: " << C.size() << "x" << C.size()
                << "\nComputation time: " << duration.count() << " seconds\n";
        logFile << "================\n";
    }

    cout << fixed << setprecision(4)
         << "\nComputation time (" << num_threads << " threads, method " << method << "): "
         << duration.count() << " s\n";
}

Matrix generateMatrix(int n) {
    Matrix M(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            M[i][j] = rand() % 10;
    return M;
}

void printMatrix(const Matrix &M, const string &name) {
    if (!enableLogging) return;
    cout << "\nMatrix " << name << ":\n";
    for (const auto &row : M) {
        for (double val : row)
            cout << setw(5) << val << " ";
        cout << "\n";
    }
}

int main() {
    srand(time(nullptr));

    int n, num_threads, method;
    char loggingChoice;

    cout << "Enter matrix size (n x n): ";
    cin >> n;
    cout << "Enter number of threads: ";
    cin >> num_threads;
    cout << "Choose method (1=row-major, 2=col-major, 3=every-k): ";
    cin >> method;
    cout << "Enable logging/printing? (y/n): ";
    cin >> loggingChoice;
    enableLogging = (loggingChoice == 'y' || loggingChoice == 'Y');

    stringstream filename;
    auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    filename << "matrix_log_" <<n<<"x"<<n<<"_"<<now << ".txt";
    if (enableLogging) {
        logFile.open(filename.str());
        if (!logFile.is_open()) {
            cerr << "Error: Could not open log file.\n";
            return 1;
        }

        logFile << "=== Matrix Multiplication Log ===\n";
        logFile << "Matrix size: " << n << "x" << n << "\n";
        logFile << "Threads: " << num_threads << "\n";
        logFile << "Method: " << method << "\n";
        logFile << "===============================\n\n";
    }

    Matrix A = generateMatrix(n);
    Matrix B = generateMatrix(n);
    Matrix C(n, vector<double>(n, 0));

    if (n <= 10) {
        printMatrix(A, "A");
        printMatrix(B, "B");
    }

    multiply(A, B, C, num_threads, method);

    if (n <= 10) printMatrix(C, "C (Result)");

    if (enableLogging) {
        logFile << "\nComputation finished successfully.\n";
        logFile.close();
        cout << "\nLog file saved as: " << filename.str() << endl;
    }

    cout << "Done.\n";
    return 0;
}
