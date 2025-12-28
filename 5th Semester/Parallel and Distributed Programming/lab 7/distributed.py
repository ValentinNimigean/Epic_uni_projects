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
    return [ (a[i] if i < len(a) else 0) + (b[i] if i < len(b) else 0) for i in range(max(len(a), len(b))) ]

def sub_poly(a, b):
    return [ (a[i] if i < len(a) else 0) - (b[i] if i < len(b) else 0) for i in range(max(len(a), len(b))) ]

def distributed_karatsuba(a, b, comm):
    size = comm.Get_size()
    rank = comm.Get_rank()
    n = len(a)

    if size < 3 or n <= 64:
        return sequential_karatsuba_local(a, b)

    m = n // 2
    a0, a1 = a[:m], a[m:]
    b0, b1 = b[:m], b[m:]

    nodes_per_group = size // 3
    


    z0, z1_star, z2 = [], [], []

    if rank < nodes_per_group:
        z0 = distributed_karatsuba(a0, b0, comm.Split(0, rank))
    elif rank < 2 * nodes_per_group:
        z2 = distributed_karatsuba(a1, b1, comm.Split(1, rank))
    elif rank < 3 * nodes_per_group:
        z1_star = distributed_karatsuba(add_poly(a0, a1), add_poly(b0, b1), comm.Split(2, rank))
    
  
    if rank == 0:
        z2 = comm.recv(source=nodes_per_group)
        z1_star = comm.recv(source=2 * nodes_per_group)
    elif rank == nodes_per_group:
        comm.send(z2, dest=0)
    elif rank == 2 * nodes_per_group:
        comm.send(z1_star, dest=0)

    if rank == 0:
        z1 = sub_poly(sub_poly(z1_star, z0), z2)
        res = [0] * (2 * n)
        for i, v in enumerate(z0): res[i] += v
        for i, v in enumerate(z1): res[i + m] += v
        for i, v in enumerate(z2): res[i + 2 * m] += v
        return res
    return None

def sequential_karatsuba_local(a, b):
    n = len(a)
    if n <= 32: return sequential_naive(a, b)
    m = n // 2
    z0 = sequential_karatsuba_local(a[:m], b[:m])
    z2 = sequential_karatsuba_local(a[m:], b[m:])
    z1_star = sequential_karatsuba_local(add_poly(a[:m], a[m:]), add_poly(b[:m], b[m:]))
    z1 = sub_poly(sub_poly(z1_star, z0), z2)
    res = [0] * (2 * n)
    for i, v in enumerate(z0): res[i] += v
    for i, v in enumerate(z1): res[i + m] += v
    for i, v in enumerate(z2): res[i + 2 * m] += v
    return res

def main():
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()
    
    n = 10000
    a = [random.randint(-5, 5) for _ in range(n)]
    b = [random.randint(-5, 5) for _ in range(n)]

    start = time.time()
    result = distributed_karatsuba(a, b, comm)
    
    if rank == 0:
        duration = (time.time() - start) * 1000
        print(f"Fully Distributed Karatsuba ({size} nodes): {duration:.2f} ms")

if __name__ == "__main__":
    main()