# Normalized Cross-Correlation (NCC)

## Overview
Normalized Cross-Correlation (NCC) is a similarity measure commonly used in image processing and computer vision, especially for **template matching**. It evaluates how closely a template image matches a region of a larger scene image while being invariant to changes in brightness and contrast.

---

## Mathematical Definition

Given:
- A **template** \( T \)
- A **scene window** \( F \) of the same size

The NCC score is defined as:

\[
\mathrm{NCC}(F, T)
=
\frac{
n \sum_{i=1}^{n} F_i T_i
-
\left( \sum_{i=1}^{n} F_i \right)
\left( \sum_{i=1}^{n} T_i \right)
}{
\sqrt{
\left(
n \sum_{i=1}^{n} F_i^2
-
\left( \sum_{i=1}^{n} F_i \right)^2
\right)
\left(
n \sum_{i=1}^{n} T_i^2
-
\left( \sum_{i=1}^{n} T_i \right)^2
\right)
}
}
\]

---

## Variable Definitions

| Symbol | Description |
|------|------------|
| \( F_i \) | Pixel intensity of the scene image at position \(i\) |
| \( T_i \) | Pixel intensity of the template image at position \(i\) |
| \( n \) | Total number of pixels in the template (\(n = \text{width} \times \text{height}\)) |
| \( \sum F_i \) | Sum of all pixel intensities in the scene window |
| \( \sum T_i \) | Sum of all pixel intensities in the template |
| \( \sum F_i^2 \) | Sum of squared scene pixel intensities |
| \( \sum T_i^2 \) | Sum of squared template pixel intensities |
| \( \sum (F_i \cdot T_i) \) | Sum of element-wise products between scene and template pixels |

---

## Interpretation of NCC Values

The NCC score lies in the range:

\[
-1 \le \mathrm{NCC} \le 1
\]

| NCC Value | Meaning |
|----------|--------|
| **1.0** | Perfect match |
| **0.0** | No correlation |
| **-1.0** | Perfect inverse match |

---

## Why Normalization Matters

The normalization term in the denominator removes:
- Global brightness shifts
- Linear contrast changes

This makes NCC robust to lighting variations between the template and the scene.

---

## Statistical Interpretation

NCC is mathematically equivalent to the **Pearson correlation coefficient** computed between the flattened vectors of the template and the scene window.

---
# Eficiency
| Technology | Accuracy (Score) | Execution Time | Speedup (vs. MPI) |
| --- | --- | --- | --- |
| **OpenCL (C# / GPU)** |  | 586 ms | ~63.5x |
| **Threaded (C++)** |  | 6,517 ms | ~5.7x |
| **MPI (6 Processes)** |  | 37,233 ms | 1.0x (Baseline) |



##
##
# Threaded Implementation



The system uses the **Pearson Correlation Coefficient** version of NCC to ensure robustness against linear lighting changes.

By calculating the sums of pixels, squares, and products, the algorithm identifies the best match regardless of absolute brightness levels.

---

### 2. Implementation Architecture

#### **Parallel Grayscale Conversion**

Instead of a single-threaded conversion, the image is divided into horizontal strips.

* **Mechanism:** `std::async` launches `grayscaleStrip` tasks.
* **Benefit:** Utilizes all CPU cores to reduce pre-processing latency.

#### **Task-Based Parallelism**

The search space is decomposed into a list of `SearchTask` objects.

1. **Scale Loop:** The template is resized (0.1x to 2.0x).
2. **Spatial Split:** For each scale, the search area is divided based on `std::thread::hardware_concurrency()`.
3. **Execution:** Tasks are pushed into a `std::vector<std::future<MatchResult>>`.

---

### 3. Synchronization & Data Handling

| Feature | Description |
| --- | --- |
| **Lock-Free Design** | No `std::mutex` is used. Threads read from shared memory but write to independent `MatchResult` structures, preventing "false sharing" and lock contention. |
| **Futures/Promises** | `std::future::get()` acts as a synchronization barrier, ensuring the main thread waits until all search segments are complete before selecting the best score. |
| **Dynamic Stride** | A configurable step size (stride) allows the algorithm to skip pixels, balancing the trade-off between processing speed and spatial accuracy. |

---

### 4. Logic Flow

1. **Load:** Read scene and template via OpenCV.
2. **Prep:** Convert both to grayscale using parallel threads.
3. **Distribute:** Calculate required scales and split the vertical search range into segments.
4. **Compute:** Run NCC calculations concurrently across all cores.
5. **Reduce:** Compare all `MatchResult` outputs to find the global maximum score.
6. **Output:** Draw bounding boxes and log performance metrics (time in ms and NCC score).


###
###
###
# Distributed Implementation

This implementation uses the **Message Passing Interface (MPI)** to distribute a multi-scale Normalized Cross-Correlation (NCC) workload across multiple processes or network nodes.

---

### 1. Parallel Strategy: Scale-Space Decomposition

Unlike the threaded version which splits a single image into strips, this MPI implementation utilizes **Data Parallelism** at the scale level:

* **Round-Robin Distribution:** The list of scales () is distributed among processes using the rank logic: `i = world_rank; i < allScales.size(); i += world_size`.
* **Independent Computation:** Each MPI process maintains its own memory space and independently resizes the template and searches the scene for its assigned scales.
* **Load Balancing:** By assigning scales in a round-robin fashion, the workload is distributed relatively evenly, even if larger scales take longer to compute than smaller ones.

---

### 2. Synchronization & Communication

The system relies on three primary MPI communication primitives:

| Primitive | Function in Code | Purpose |
| --- | --- | --- |
| **`MPI_Bcast`** | Broadcast | Rank 0 reads the `config.txt` and sends the paths and settings to all other processes simultaneously. |
| **`MPI_Barrier`** | Barrier | Ensures all processes have finished loading images and pre-processing before the timer starts. |
| **`MPI_Gather`** | Gather | Collects the `localBest` result (score, x, y, scale) from every worker and sends it back to the Master (Rank 0). |
| **`MPI_Wtime`** | Wall Clock | Provides high-resolution timing across the distributed environment. |

---

### 3. Logic Flow (Master vs. Worker)

#### **The Master (Rank 0)**

1. **Orchestration:** Loads configuration and broadcasts it to the cluster.
2. **Participation:** Performs its own share of scale-searches just like a worker.
3. **Reduction:** After the `MPI_Gather`, it iterates through the results from all processes to find the **Global Maximum** score.
4. **Output:** Handles all file I/O, generating the result image and logging performance to `log.txt`.

#### **The Workers (Rank > 0)**

1. **Receive:** Wait for the broadcasted configuration and image paths.
2. **Compute:** Execute the NCC search for their assigned subset of scales.
3. **Report:** Send their best local match to the Master via the gather operation and shut down via `MPI_Finalize`.

---

### 4. Key Performance Differences

* **Memory Usage:** Unlike threading, MPI processes do not share memory. Each process loads its own copy of the scene and template, increasing total RAM usage.
* **Scalability:** This version can be run across a cluster of different computers, not just a single CPU.
* **OpenCV Interaction:** `cv::setNumThreads(0)` is called to prevent OpenCV's internal threading from conflicting with the MPI process management, ensuring each process stays on its assigned core.

---

###
###
###
###
###
###

# GPU Accelerated Implementation



This implementation leverages **OpenCL (via Silk.NET)** and **C# (OpenCvSharp)** to offload the heavy Normalized Cross-Correlation (NCC) calculations to the GPU. This allows for massive parallelization across thousands of GPU threads.

---

### 1. The GPU Kernel (`ncc_search`)

The heart of this implementation is the OpenCL C kernel code. Unlike CPU threads, which handle large "strips" of an image, each GPU thread handles the calculation for a **single sliding window position**.

* **Work-Item Mapping:** Each global ID `(gid_x, gid_y)` corresponds to a specific  coordinate in the search scene.
* **Memory Access:** The kernel reads from `__global uchar* scene` and `__global uchar* templ` buffers.
* **Mathematical Operations:** It calculates the sums () locally within the thread and stores the resulting NCC score in an `output` float array.

---

### 2. Implementation Architecture (C# & OpenCL)

| Component | Responsibility |
| --- | --- |
| **Host (C#)** | Manages image loading, memory allocation on the GPU, and the multi-scale loop (0.1x to 2.0x). |
| **Device (GPU)** | Executes the `ncc_search` kernel across a 2D grid of work-items. |
| **Command Queue** | Orchestrates the transfer of data (buffers) between RAM and VRAM. |
| **NDRange** | Defines the "grid" size (Width/Stride  Height/Stride) that the GPU executes. |

---

### 3. Synchronization & Memory Management

This implementation uses **Explicit Memory Management** to ensure high performance:

1. **Buffer Creation:** `CreateBuffer` allocates memory on the GPU (VRAM). The scene is uploaded once, while the resized template is uploaded for every scale change.
2. **Kernel Arguments:** `SetKernelArg` passes pointers and constants (like `sumT` and `sumTT`) to the GPU.
3. **Asynchronous Execution:** `EnqueueNdrangeKernel` starts the GPU processing without blocking the C# thread.
4. **Data Retrieval:** `EnqueueReadBuffer` brings the result "score map" back to the CPU for the final reduction (finding the maximum value).

---

### 4. Logic Flow

1. **Initialize:** Detect the GPU platform and build the OpenCL program from the `KernelSource` string.
2. **Upload:** Transfer the grayscale scene image to the GPU VRAM.
3. **Scale Loop:** * Resize the template on the CPU.
* Calculate template constants (, ).
* Upload the new template to the GPU.
* **Execute Kernel:** GPU processes all  positions in parallel.
* **Download:** Read the results back and track the highest score.


4. **Finalize:** Release GPU memory objects and visualize the match using OpenCV.

---

### 5. Performance Advantages

* **Massive Parallelism:** While a CPU might have 16 threads, a modern GPU has thousands of cores, making the  NCC operation significantly faster.
* **Reduced Latency:** By using `float` for kernel math and `INTER_NEAREST` for resizing, the system prioritizes throughput.