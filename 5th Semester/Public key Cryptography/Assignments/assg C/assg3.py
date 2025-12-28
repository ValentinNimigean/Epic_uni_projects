# ---------------------------------------------------------
# RSA Encryption for 27-letter Alphabet
# e is automatically chosen as the smallest valid odd prime
# ---------------------------------------------------------

import math

# Alphabet mapping
alphabet = "_ABCDEFGHIJKLMNOPQRSTUVWXYZ"
char_to_num = {ch: i for i, ch in enumerate(alphabet)}
num_to_char = {i: ch for i, ch in enumerate(alphabet)}

# Convert plaintext block (k letters) → number
def block_to_number(block):
    value = 0
    for ch in block:
        value = value * 27 + char_to_num[ch]
    return value

# Convert number → ciphertext block (l letters)
def number_to_block(num, l):
    chars = []
    for _ in range(l):
        chars.append(num_to_char[num % 27])
        num //= 27
    return "".join(reversed(chars))

# Fast modular exponentiation
def modexp(base, exp, mod):
    result = 1
    base %= mod
    while exp > 0:
        if exp & 1:
            result = (result * base) % mod
        base = (base * base) % mod
        exp >>= 1
    return result

# Find the smallest odd prime e such that gcd(e, φ(n)) = 1
def choose_e(phi):
    primes = [3, 5, 7, 11, 13, 17, 19, 23, 29, 31]
    for e in primes:
        if math.gcd(e, phi) == 1:
            return e
    raise ValueError("No suitable prime e found (unexpected).")

def rsa_encrypt(plaintext, k, l, p, q):
    plaintext = plaintext.replace(" ", "").upper()

    # Compute n and phi(n)
    n = p * q
    phi = (p - 1) * (q - 1)

    # Choose valid e automatically
    e = choose_e(phi)

    print("\n--- RSA PARAMETERS ---")
    print(f"p = {p}, q = {q}")
    print(f"n = {n}")
    print(f"phi(n) = {phi}")
    print(f"Chosen e = {e}")

    # Pad plaintext if needed
    while len(plaintext) % k != 0:
        plaintext += "_"

    # Split into blocks of k letters
    blocks = [plaintext[i:i+k] for i in range(0, len(plaintext), k)]
    print("\nPlaintext blocks:", blocks)

    # Convert plaintext blocks → numbers
    numeric_blocks = [block_to_number(b) for b in blocks]
    print("Numeric plaintext:", numeric_blocks)

    # Encrypt each block
    encrypted_nums = [modexp(b, e, n) for b in numeric_blocks]
    print("Encrypted numbers:", encrypted_nums)

    # Convert encrypted numbers → l-letter blocks
    cipher_blocks = [number_to_block(c, l) for c in encrypted_nums]
    ciphertext = "".join(cipher_blocks)

    print("Ciphertext blocks:", cipher_blocks)
    print("\n*** FINAL CIPHERTEXT ***")
    print(ciphertext)

    return ciphertext


# ---------------------------------------------------------
# MAIN PROGRAM
# ---------------------------------------------------------

if __name__ == "__main__":
    print("RSA Encryption (27-letter Alphabet)\n")

    plaintext = input("Enter plaintext: ").strip()
    k = int(input("Enter plaintext block size k: "))
    l = int(input("Enter ciphertext block size l: "))
    p = int(input("Enter prime p: "))
    q = int(input("Enter prime q: "))

    rsa_encrypt(plaintext, k, l, p, q)
