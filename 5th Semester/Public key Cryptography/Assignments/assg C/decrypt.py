# ---------------------------------------------------------
# RSA Decryption for 27-letter Alphabet
# e is chosen automatically; d = e^{-1} mod phi(n)
# ---------------------------------------------------------

import math

# Alphabet mapping
alphabet = "_ABCDEFGHIJKLMNOPQRSTUVWXYZ"
char_to_num = {ch: i for i, ch in enumerate(alphabet)}
num_to_char = {i: ch for i, ch in enumerate(alphabet)}

def modexp(base, exp, mod):
    """Fast modular exponentiation."""
    result = 1
    base %= mod
    while exp > 0:
        if exp & 1:
            result = (result * base) % mod
        base = (base * base) % mod
        exp >>= 1
    return result

def choose_e(phi):
    """Choose smallest valid odd prime e with gcd(e, phi) = 1."""
    primes = [3, 5, 7, 11, 13, 17, 19, 23, 29, 31]
    for e in primes:
        if math.gcd(e, phi) == 1:
            return e
    raise ValueError("No valid encryption exponent found.")

def mod_inverse(a, m):
    """Compute modular inverse using Extended Euclidean Algorithm."""
    r0, r1 = a, m
    s0, s1 = 1, 0
    t0, t1 = 0, 1

    while r1 != 0:
        q = r0 // r1
        r0, r1 = r1, r0 - q * r1
        s0, s1 = s1, s0 - q * s1
        t0, t1 = t1, t0 - q * t1

    if r0 != 1:
        raise ValueError("No modular inverse exists.")

    return s0 % m

def number_to_block_k(num, k):
    """Convert decrypted number into a block of k letters."""
    chars = []
    for _ in range(k):
        chars.append(num_to_char[num % 27])
        num //= 27
    return "".join(reversed(chars))


def block_to_number_l(block):
    """Convert l-letter ciphertext block to number."""
    value = 0
    for ch in block:
        value = value * 27 + char_to_num[ch]
    return value


def rsa_decrypt(ciphertext, k, l, p, q):
    ciphertext = ciphertext.replace(" ", "").upper()

    # Compute n and phi(n)
    n = p * q
    phi = (p - 1) * (q - 1)

    # Choose e and compute d
    e = choose_e(phi)
    d = mod_inverse(e, phi)

    print("\n--- RSA PARAMETERS ---")
    print(f"p = {p}, q = {q}")
    print(f"n = {n}")
    print(f"phi(n) = {phi}")
    print(f"Chosen e = {e}")
    print(f"Computed d = {d}")

    # Split ciphertext into l-letter blocks
    blocks = [ciphertext[i:i+l] for i in range(0, len(ciphertext), l)]
    print("\nCiphertext blocks:", blocks)

    # Convert ciphertext blocks → numbers
    numeric_blocks = [block_to_number_l(b) for b in blocks]
    print("Numeric ciphertext:", numeric_blocks)

    # Apply RSA decryption m = c^d mod n
    decrypted_nums = [modexp(c, d, n) for c in numeric_blocks]
    print("Decrypted numeric values:", decrypted_nums)

    # Convert numbers → k-letter plaintext blocks
    plaintext_blocks = [number_to_block_k(m, k) for m in decrypted_nums]
    plaintext = "".join(plaintext_blocks)

    print("Plaintext blocks:", plaintext_blocks)
    print("\n*** FINAL PLAINTEXT ***")
    print(plaintext)

    return plaintext


# ---------------------------------------------------------
# MAIN PROGRAM
# ---------------------------------------------------------

if __name__ == "__main__":
    print("RSA Decryption (27-letter Alphabet)\n")

    ciphertext = input("Enter ciphertext: ").strip()
    k = int(input("Enter plaintext block size k: "))
    l = int(input("Enter ciphertext block size l: "))
    p = int(input("Enter prime p: "))
    q = int(input("Enter prime q: "))

    rsa_decrypt(ciphertext, k, l, p, q)
