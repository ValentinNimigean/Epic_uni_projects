import random
import math

# (i) Setting. The alphabet will have 27 characters: the blank and the 26 letters of the English alphabet.
ALPHABET = " abcdefghijklmnopqrstuvwxyz"

def get_prime(bits):
    """
    Generates a prime number with the specified number of bits using Miller-Rabin test.
    """
    while True:
        n = random.getrandbits(bits)
        # Ensure it's odd
        if n % 2 == 0:
            n += 1
        if is_prime(n):
            return n

def is_prime(n, k=40):
    """
    Miller-Rabin primality test.
    k is the number of rounds.
    """
    if n == 2 or n == 3: return True
    if n % 2 == 0 or n < 2: return False

    # Find r and s such that n - 1 = 2^s * r
    r, s = 0, n - 1
    while s % 2 == 0:
        r += 1
        s //= 2
    
    for _ in range(k):
        a = random.randrange(2, n - 1)
        x = pow(a, s, n)
        if x == 1 or x == n - 1:
            continue
        for _ in range(r - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
    return True

def lcm(a, b):
    """Compute least common multiple."""
    return abs(a * b) // math.gcd(a, b)

def egcd(a, b):
    """Extended Euclidean Algorithm."""
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)

def modinv(a, m):
    """Computes the modular multiplicative inverse of a modulo m."""
    g, x, y = egcd(a, m)
    if g != 1:
        raise Exception('Modular inverse does not exist')
    return x % m

def L(x, n):
    """Paillier L function: L(u) = (u - 1) / n"""
    return (x - 1) // n

def generate_keys(bit_length=512):
    """
    (ii) The algorithm Generates a public key and a private key.
    The public key will be randomly generated in the required interval.
    """
    # 1. Select two large primes p and q
    p = get_prime(bit_length)
    q = get_prime(bit_length)
    while p == q:
        q = get_prime(bit_length)
    
    n = p * q
    nsquare = n * n
    
    # 2. Compute lambda = lcm(p-1, q-1) - Carmichael’s function
    #for any random g, (g^lamb) mod n == 1
    lamb = lcm(p - 1, q - 1)
    
    # 3. Select random integer g in Z*_{n^2}
    # "The public key will be randomly generated in the required interval."
    while True:
        g = random.randint(1, nsquare - 1)
        if math.gcd(g, nsquare) == 1:
            # Verify g by checking if modular inverse exists for L(g^lambda mod n^2) mod n
            u = pow(g, lamb, nsquare)
            l_u = L(u, n)
            if math.gcd(l_u, n) == 1:
                mu = modinv(l_u, n)
                break
                
    public_key = (n, g)
    private_key = (lamb, mu)
    
    return public_key, private_key

def word_to_int(word):
    """
    Converts a word to a large integer based on the 27-character alphabet.
    """
    word = word.lower()
    value = 0
    for char in word:
        if char in ALPHABET:
            idx = ALPHABET.index(char)
            value = value * 27 + idx
        else:
            print(f"Warning: Character '{char}' ignored.")
    return value


def int_to_word(value):
    """Converts a large integer back to a string based on the 27-character alphabet."""
    chars = []
    if value == 0: return ALPHABET[0]
    while value > 0:
        chars.append(ALPHABET[value % 27])
        value //= 27
    return "".join(reversed(chars))

def encrypt(public_key, message_word):
    """
    Encrypts a word using the Paillier cryptosystem.
    """
    n, g = public_key
    nsquare = n * n
    
    # Convert message word to integer m
    m = word_to_int(message_word)
    
    # Check if m < n
    if m >= n:
        raise ValueError(f"Message value {m} is too large for modulus n {n}. Use larger keys or shorter words.")
    
    # Select random r where 0 < r < n and gcd(r, n) = 1
    while True:
        r = random.randint(1, n - 1)
        if math.gcd(r, n) == 1:
            break
            
    # Compute ciphertext c = g^m * r^n mod n^2
    c = (pow(g, m, nsquare) * pow(r, n, nsquare)) % nsquare
    return c



def decrypt(public_key, private_key, ciphertext):
    """
    Decrypts a ciphertext using the Paillier private key.
    """
    n, g = public_key
    lamb, mu = private_key
    nsquare = n * n

    print("\n" + "="*50)
    print("INTERNAL PARAMETERS")
    print("-"*50)
    print(f"n:       {n}")
    print(f"g:       {g}")
    print(f"lambda:  {lamb}")
    print(f"mu:      {mu}")
    print(f"nsquare: {nsquare}")
    print("-"*50)
    
    print("-" * 50)
    print("BEGINNING DECRYPTION PROCESS")
    print("-" * 50)
    print(f"1. Input Ciphertext (c):\n   {ciphertext}\n")
    
    # Step 1: Compute u = c^lambda mod n^2
    u = pow(ciphertext, lamb, nsquare)
    print(f"2. Computed u = c^λ mod n²:\n   {u}\n")
    
    # Step 2: Apply the L function
    # L(u) = (u - 1) / n
    l_u = L(u, n)
    print(f"3. Applied L function L(u) = (u-1)/n:\n   {l_u}\n")
    
    # Step 3: Compute the plaintext integer m
    # m = L(u) * mu mod n
    m = (l_u * mu) % n
    print(f"4. Computed plaintext integer (m = L(u) * μ mod n):\n   {m}\n")
    
    # Step 4: Convert integer back to string
    decrypted_word = int_to_word(m)
    print(f"5. Final Decoded String:\n   '{decrypted_word}'")
    print("-" * 30)
    
    return decrypted_word

if __name__ == "__main__":
    # 1. Key Generation
    print("Generating keys...")
    pub, priv = generate_keys(bit_length=256) # 256 for speed,2048 for security
    
    # 2. Encryption
    original_text = "banana"
    print(f"\nOriginal Message: {original_text}")
    
    ciphertext = encrypt(pub, original_text)
    print(f"Ciphertext: {ciphertext}")
    
    # 3. Decryption
    decrypted_text = decrypt(pub, priv, ciphertext)
    print(f"Decrypted Message: {decrypted_text}")