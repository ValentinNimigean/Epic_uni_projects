from mpi4py import MPI
import time
import random
import os

def sequential_naive(a, b):
    n, m = len(a), len(b)
    res = [0] * (n + m - 1)
    for i in range(n):
        for j in range(m):
            res[i + j] += a[i] * b[j]
    return res

def add_poly(a, b):
    res = [0] * max(len(a), len(b))
    for i in range(len(a)): res[i] += a[i]
    for i in range(len(b)): res[i] += b[i]
    return res

def sub_poly(a, b):
    res = [0] * max(len(a), len(b))
    for i in range(len(a)): res[i] += a[i]
    for i in range(len(b)): res[i] -= b[i]
    return res

def sequential_karatsuba(a, b):
    n = len(a)
    if n <= 32:
        return sequential_naive(a, b)
    
    m = n // 2
    a0, a1 = a[:m], a[m:]
    b0, b1 = b[:m], b[m:]
    
    z0 = sequential_karatsuba(a0, b0)
    z2 = sequential_karatsuba(a1, b1)
    
    z1_star = sequential_karatsuba(add_poly(a0, a1), add_poly(b0, b1))
    z1 = sub_poly(sub_poly(z1_star, z0), z2)
    
    res = [0] * (2 * n)
    for i, val in enumerate(z0): res[i] += val
    for i, val in enumerate(z1): res[i + m] += val
    for i, val in enumerate(z2): res[i + 2 * m] += val
    return res

def main():
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()
    
    RUN_NAIVE = 1
    RUN_KARATSUBA = 2
    STOP = 0

    if rank == 0:
        log_file = os.path.join(os.path.dirname(__file__), "mpi_results.txt")
        sizes = [1000, 5000, 10000, 20000]
        
        with open(log_file, "w") as f:
            f.write(f"Python MPI Results (Scatter/Gather) - Nodes: {size}\n")
            f.write("==============================================\n\n")

        for n in sizes:
            print(f"[Master] Testing size {n}...")
            padded_n = ((n + size - 1) // size) * size
            a = [random.randint(-10, 10) for _ in range(padded_n)]
            b = [random.randint(-10, 10) for _ in range(n)]

            for i in range(1, size): comm.send(RUN_NAIVE, dest=i)
            
            start_time = time.time()
            
            comm.bcast(b, root=0)
            
            chunk_size = padded_n // size
            a_chunks = [a[i*chunk_size : (i+1)*chunk_size] for i in range(size)]
            local_a = comm.scatter(a_chunks, root=0)
            
            local_res = sequential_naive(local_a, b)
            
            all_parts = comm.gather(local_res, root=0)
            
            final_res_naive = [0] * (2 * padded_n)
            for i, part in enumerate(all_parts):
                offset = i * chunk_size
                for j, val in enumerate(part):
                    final_res_naive[offset + j] += val
            
            t_naive = (time.time() - start_time) * 1000

            if size >= 3:
                for i in range(1, 3): comm.send(RUN_KARATSUBA, dest=i)
                m = n // 2
                start_time = time.time()
                comm.send((a[:m], b[:m]), dest=1)
                comm.send((a[m:2*m], b[m:2*m]), dest=2)
                
                z1_star = sequential_karatsuba(add_poly(a[:m], a[m:2*m]), add_poly(b[:m], b[m:2*m]))
                z0 = comm.recv(source=1)
                z2 = comm.recv(source=2)
                
                z1 = sub_poly(sub_poly(z1_star, z0), z2)
                final_res_kar = [0] * (2 * n)
                for i, v in enumerate(z0): final_res_kar[i] += v
                for i, v in enumerate(z1): final_res_kar[i + m] += v
                for i, v in enumerate(z2): final_res_kar[i + 2 * m] += v
                t_kar = (time.time() - start_time) * 1000
            else:
                t_kar = 0 

            with open(log_file, "a") as f:
                f.write(f"Size {n}:\n  Naive (Scatter): {t_naive:.2f} ms\n  Karatsuba: {t_kar:.2f} ms\n\n")

        for i in range(1, size): comm.send(STOP, dest=i)
        print(f"Master finished. Results in {log_file}")

    else:
        while True:
            task = comm.recv(source=0)
            if task == STOP: break
            
            if task == RUN_NAIVE:
                b = comm.bcast(None, root=0)
                local_a = comm.scatter(None, root=0)
                local_res = sequential_naive(local_a, b)
                comm.gather(local_res, root=0)
                
            elif task == RUN_KARATSUBA:
                sub_a, sub_b = comm.recv(source=0)
                res = sequential_karatsuba(sub_a, sub_b)
                comm.send(res, dest=0)

if __name__ == "__main__":
    main()