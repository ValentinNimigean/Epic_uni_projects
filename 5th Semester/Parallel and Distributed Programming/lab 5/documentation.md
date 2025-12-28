# Lab 5 — Parallelizing Techniques  
## Polynomial Multiplication: Sequential vs Parallel, Naive vs Karatsuba  
### Parallel and Distributed Programming — 2025

# Introduction

The objective of this lab is to implement and analyze four different polynomial multiplication algorithms:

1. **Naive Sequential**  
2. **Naive Parallelized**  
3. **Karatsuba Sequential**  
4. **Karatsuba Parallelized**

Additionally, the lab includes a **bonus requirement**:  
performing the same computations with **large integer (BigInteger)** coefficients.

The documentation describes:

- The **algorithms**  
- The **synchronization** used  
- The **performance measurements** obtained  

All code was written in **C# (.NET)**.



# Polynomials and Representation

A polynomial of degree *n* is:

\[
P(x) = a_0 + a_1x + a_2 x^2 + \ldots + a_n x^n
\]

It is represented in code as an array:
[ a0, a1, a2, …, an ]


Polynomial multiplication corresponds to **discrete convolution** of the coefficient arrays.



# Algorithms Implemented

## 1. Naive Sequential Algorithm

### Description
This is the classical O(n²) algorithm using two nested loops:

\[
C_k = \sum_{i+j=k} a_i b_j
\]

Pseudocode:
for i = 0..n-1:
\
for j = 0..m-1:
\
result[i+j] += a[i] * b[j]


### Complexity
- **Time:** O(n²)  
- **Space:** O(n)  
- Simple and reliable baseline.


## 2. Naive Parallel Algorithm

### Description
The same computation is parallelized using `Parallel.For`.

However, multiple threads may write to the same index `result[k]`.  
This leads to race conditions that must be synchronized.

### Synchronization
Because `BigInteger` cannot be used with `Interlocked.CompareExchange`,  
we use **one lock per result index**:
lock(locks[k]):
result[k] += product

### Benefits
- Fine-grained locking → minimal contention  
- Safe and correct parallel updates  
- Avoids a global lock completely  

### Complexity
- Same O(n²) work  
- Speedup visible for larger inputs  

---

## 3. Karatsuba Sequential Algorithm

### Description

Karatsuba is a divide-and-conquer algorithm that reduces the number of multiplications.

Split polynomials:

\[
A = A_0 + x^n A_1,\quad B = B_0 + x^n B_1
\]

Compute three products:

\[
Z_0 = A_0B_0
\]
\[
Z_2 = A_1B_1
\]
\[
Z_1^\* = (A_0 + A_1)(B_0 + B_1)
\]

Middle term:

\[
Z_1 = Z_1^\* - Z_0 - Z_2
\]

Reconstruction:

\[
C = Z_0 + x^n Z_1 + x^{2n} Z_2
\]

### Complexity
\[
T(n) = 3T(n/2) + O(n) = O(n^{1.585})
\]

Much faster than O(n²) for large n.

---

## 4. Karatsuba Parallel Algorithm

### Description
Karatsuba’s three recursive multiplications are independent:

- Z₀  
- Z₂  
- Z₁*  

Each is computed using `Task.Run`:

t0 = Task.Run(Z0 computation)
t1 = Task.Run(Z2 computation)
t2 = Task.Run(Z1* computation)
Task.WaitAll(t0, t1, t2)


### Synchronization
- **No locks needed**, since each recursive call writes to its **own array**
- Only synchronization is:
  
Task.WaitAll(...)

### Depth Limiting
To avoid thread explosion:

if (depth < 4) parallel
else sequential

This matches the recursive decomposition principles from lecture materials.

---

# Synchronization

| Algorithm | Shared Writes? | Method Used | Notes |
|-----------|----------------|-------------|-------|
| Naive Sequential | No | None | Single-threaded |
| Naive Parallel | Yes | Per-index locks | Ensures atomicity of `result[k]` updates |
| Karatsuba Sequential | No | None | Purely recursive, no sharing |
| Karatsuba Parallel | No | Task.WaitAll | Subtasks have no shared state |

### Why Karatsuba requires no locks
Each recursive call:

- Allocates its own arrays (A₀, A₁, B₀, B₁, results)
- Writes only to those private arrays  
- Combines results only after all tasks finish

Thus **no races are possible**.


# Performance Measurements

All measurements were recorded into `results.txt` automatically.

Two test types were used:


## Small Coefficient Results  
- Coefficients in range **[-50, 50]**  
- Sizes: **64, 128, 256, 512**

### Observed Trends
- Naive sequential slows down quadratically  
- Naive parallel overtakes sequential for n ≥ ~128  
- Karatsuba sequential is faster for larger input sizes  
- Karatsuba parallel is generally the fastest for n ≥ 256  


## Big Coefficient Results (Bonus)  
- Random **256-bit** BigIntegers  
- Sizes: **64, 128**

### Observed Trends
- BigInteger multiplication is expensive  
- Karatsuba’s reduction from 4 → 3 multiplications produces major speedups  
- Karatsuba parallel is consistently fastest  
- Naive parallel gains less benefit because BigInteger additions dominate  


# Conclusion

This lab demonstrates the contrast between:

- **Data parallelism** (naive parallel)  
- **Task parallelism** (Karatsuba parallel)  
- **O(n²)** vs. **O(n¹·⁵⁸⁵)** algorithms  
- Effects of synchronization and thread overhead  

Key takeaways:

- Parallelization only helps when the workload is large enough  
- Fine-grained locking is necessary for thread-safe O(n²) multiplication  
- Task-based parallel recursion is ideal for divide-and-conquer algorithms  
- BigIntegers highlight algorithmic differences dramatically  
- Karatsuba parallel is the best-performing approach overall  

All four required implementations were completed and tested,  
and the bonus requirement was satisfied as well.

