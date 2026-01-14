#define CL_HPP_ENABLE_EXCEPTIONS // Enables cl::Error
#define CL_HPP_TARGET_OPENCL_VERSION 200 // Targets OpenCL 2.0+

#include <CL/opencl.hpp> // Modern wrapper header
#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <random>

// Helper to generate random coefficients
std::vector<int> generate_random_poly(int n) {
    std::vector<int> poly(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(-50, 50);
    for (int i = 0; i < n; i++) {
        poly[i] = dist(gen);
    }
    return poly;
}

int main() {
    int n;
    std::cout << "Enter polynomial size (N): ";
    if (!(std::cin >> n)) return 1;

    auto h_A = generate_random_poly(n);
    auto h_B = generate_random_poly(n);
    int res_size = 2 * n - 1;
    std::vector<int> h_C(res_size);

    try {
        // 1. Setup Platform and Device
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);
        if (platforms.empty()) throw cl::Error(1, "No OpenCL platforms found");

        cl::Device device;
        std::vector<cl::Device> devices;
        platforms[0].getDevices(CL_DEVICE_TYPE_ALL, &devices);
        if (devices.empty()) throw cl::Error(1, "No OpenCL devices found");
        device = devices[0];

        cl::Context context(device);
        cl::CommandQueue queue(context, device);

        // 2. Load and Compile Kernel
        std::ifstream kernel_file("kernel.cl");
        if (!kernel_file.is_open()) throw cl::Error(1, "Failed to open kernel.cl");
        
        std::string src(std::istreambuf_iterator<char>(kernel_file), (std::istreambuf_iterator<char>()));
        cl::Program::Sources sources;
        sources.push_back({src.c_str(), src.length()});
        
        cl::Program program(context, sources);
        try {
            program.build({device});
        } catch (cl::Error& e) {
            // Print build log if compilation fails
            std::cerr << "Build Log:\n" << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) << std::endl;
            throw e;
        }

        // 3. Create GPU Buffers
        cl::Buffer d_A(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * n, h_A.data());
        cl::Buffer d_B(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int) * n, h_B.data());
        cl::Buffer d_C(context, CL_MEM_WRITE_ONLY, sizeof(int) * res_size);

        // 4. Setup Kernel & Arguments
        cl::Kernel kernel(program, "multiply_poly");
        kernel.setArg(0, d_A);
        kernel.setArg(1, n);
        kernel.setArg(2, d_B);
        kernel.setArg(3, n); 
        kernel.setArg(4, d_C);

        // 5. Execution & Timing
        auto start = std::chrono::high_resolution_clock::now();
        
        queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(res_size), cl::NullRange);
        queue.finish(); 
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        // 6. Retrieve Results
        queue.enqueueReadBuffer(d_C, CL_TRUE, 0, sizeof(int) * res_size, h_C.data());

        std::cout << "Successfully multiplied polynomials of size " << n << std::endl;
        std::cout << "GPU Time: " << duration.count() << " ms" << std::endl;

    } catch (cl::Error& err) {
        std::cerr << "OpenCL Error: " << err.what() << " (" << err.err() << ")" << std::endl;
    }

    return 0;
}