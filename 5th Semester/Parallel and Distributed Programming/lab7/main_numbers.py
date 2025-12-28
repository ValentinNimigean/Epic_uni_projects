from mpi4py import MPI
import time
import random
import os

def sequential_naive_numbers(num1_list, num2_list):
    """Multiplies two numbers represented as lists of digits."""
    res = [0] * (len(num1_list) + len(num2_list))
    for i in range(len(num1_list)):
        carry = 0
        for j in range(len(num2_list)):
            temp = res[i + j] + num1_list[i] * num2_list[j] + carry
            res[i + j] = temp % 10
            carry = temp // 10
        res[i + len(num2_list)] += carry
    return res

def handle_carries(digits):
    """Helper to fix carries after addition/subtraction in Karatsuba."""
    carry = 0
    for i in range(len(digits)):
        digits[i] += carry
        carry = digits[i] // 10
        digits[i] %= 10
    if carry:
        digits.append(carry)
    return digits

def add_numbers(a, b):
    res = [0] * max(len(a), len(b))
    carry = 0
    for i in range(len(res)):
        val_a = a[i] if i < len(a) else 0
        val_b = b[i] if i < len(b) else 0
        s = val_a + val_b + carry
        res[i] = s % 10
        carry = s // 10
    if carry: res.append(carry)
    return res

def sub_numbers(a, b):
    res = [0] * max(len(a), len(b))
    borrow = 0
    for i in range(len(res)):
        val_a = a[i] if i < len(a) else 0
        val_b = b[i] if i < len(b) else 0
        s = val_a - val_b - borrow
        if s < 0:
            s += 10
            borrow = 1
        else:
            borrow = 0
        res[i] = s
    return res

def sequential_karatsuba_numbers(a, b):
    n = max(len(a), len(b))
    if n <= 32:
        return sequential_naive_numbers(a, b)
    
    m = n // 2
    a0, a1 = a[:m], a[m:]
    b0, b1 = b[:m], b[m:]
    
    z0 = sequential_karatsuba_numbers(a0, b0)
    z2 = sequential_karatsuba_numbers(a1, b1)
    
    a0a1 = add_numbers(a0, a1)
    b0b1 = add_numbers(b0, b1)
    z1_star = sequential_karatsuba_numbers(a0a1, b0b1)
    
    z1 = sub_numbers(sub_numbers(z1_star, z0), z2)
    
    res = [0] * (2 * n + 2)
    for i, v in enumerate(z0): res[i] += v
    for i, v in enumerate(z1): res[i + m] += v
    for i, v in enumerate(z2): res[i + 2 * m] += v
    
    return handle_carries(res)

def main():
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()
    
    RUN_NAIVE = 1
    RUN_KARATSUBA = 2
    STOP = 0

    if rank == 0:
        log_file = os.path.join(os.path.dirname(__file__), "mpi_numbers_results.txt")
        sizes = [1000, 5000, 10000]
        
        with open(log_file, "w") as f:
            f.write(f"MPI Large Number Multiplication - Nodes: {size}\n\n")

        for n in sizes:
            print(f"[Master] Multiplying numbers with {n} digits...")
            num1 = [random.randint(0, 9) for _ in range(n)]
            num2 = [random.randint(0, 9) for _ in range(n)]

            for i in range(1, size): comm.send(RUN_NAIVE, dest=i)
            comm.bcast(num2, root=0)
            
            start_time = time.time()
            chunk = n // size
            for i in range(1, size):
                comm.send(num1[i*chunk : (i+1)*chunk if i != size-1 else n], dest=i)
            
            master_part = sequential_naive_numbers(num1[:chunk], num2)
            
            for i in range(1, size):
                comm.recv(source=i) 
            
            t_naive = (time.time() - start_time) * 1000

            if size >= 3:
                for i in range(1, 3): comm.send(RUN_KARATSUBA, dest=i)
                m = n // 2
                start_time = time.time()
                comm.send((num1[:m], num2[:m]), dest=1)
                comm.send((num1[m:], num2[m:]), dest=2)
                
                z1_star = sequential_karatsuba_numbers(add_numbers(num1[:m], num1[m:]), add_numbers(num2[:m], num2[m:]))
                z0 = comm.recv(source=1)
                z2 = comm.recv(source=2)
                
                t_kar = (time.time() - start_time) * 1000
            else:
                t_kar = 0

            with open(log_file, "a") as f:
                f.write(f"Digits {n}:\n  Naive: {t_naive:.2f} ms\n  Karatsuba: {t_kar:.2f} ms\n\n")

        for i in range(1, size): comm.send(STOP, dest=i)
        print("Done.")

    else:
        while True:
            task = comm.recv(source=0)
            if task == STOP: break
            if task == RUN_NAIVE:
                num2 = comm.bcast(None, root=0)
                num1_chunk = comm.recv(source=0)
                res = sequential_naive_numbers(num1_chunk, num2)
                comm.send(res, dest=0)
            elif task == RUN_KARATSUBA:
                a, b = comm.recv(source=0)
                res = sequential_karatsuba_numbers(a, b)
                comm.send(res, dest=0)

if __name__ == "__main__":
    main()