import secrets
import sys


class RabinEncryptor:
    def __init__(self, key_size_bits=512):
        """
        Initializes the cryptosystem.
        Args:
            key_size_bits: Approximate size of the primes p and q.
        """
        self.key_size = key_size_bits
        self.n = None  # Public Key
        self._p = None  # Private Key
        self._q = None  # Private Key

        self.alphabet = " abcdefghijklmnopqrstuvwxyz"
        self.char_to_int = {c: i for i, c in enumerate(self.alphabet)}

    def _is_prime(self, n, k=40):
        """Miller-Rabin primality test for key generation."""
        if n == 2 or n == 3: return True
        if n % 2 == 0 or n < 2: return False

        r, d = 0, n - 1
        while d % 2 == 0:
            r += 1
            d //= 2

        #Miller-Rabin test
        for _ in range(k):
            #a in [2,n-2], witness for primality of n
            a = secrets.randbelow(n - 4) + 2
            x = pow(a, d, n)
            if x == 1 or x == n - 1:
                continue
            for _ in range(r - 1):
                x = pow(x, 2, n)
                if x == n - 1:
                    break
            else:#if for didn't hit break
                return False
        return True

    def _get_blum_prime(self):
        """Generates a prime p such that p = 3 mod 4."""
        while True:
            # Generate random odd number
            candidate = secrets.randbits(self.key_size)
            if candidate % 2 == 0:
                candidate += 1

            # Ensure it satisfies p = 3 mod 4
            if candidate % 4 != 3:
                candidate += 2

            if self._is_prime(candidate):
                return candidate

    def generate_keys(self):
        print("Generating keys (this might take a moment)...")
        self._p = self._get_blum_prime()
        self._q = self._get_blum_prime()

        # Ensure p != q
        while self._p == self._q:
            self._q = self._get_blum_prime()

        self.n = self._p * self._q
        print(f"Keys generated!")
        print(f"Public Key (n) size: {self.n.bit_length()} bits")
        print(f"Public Key (n): {self.n}\n")

    def _text_to_int(self, text):
        """
        Converts text to integer using Base-27 encoding.
        Formula: val = char_val * 27^position
        """
        if not all(c in self.alphabet for c in text):
            raise ValueError("Text contains invalid characters. Only a-z and space allowed.")

        total_val = 0
        # Process from right to left (least significant char first)
        # However, for reading left-to-right, we usually treat first char as most significant.
        # Let's treat the string like a number: "ab" -> a is 27s place, b is 1s place.
        for char in text:
            total_val = total_val * 27 + self.char_to_int[char]

        return total_val

    def encrypt(self, plaintext):
        if self.n is None:
            raise Exception("Keys not generated. Run generate_keys() first.")

        print(f"--- Encrypting: '{plaintext}' ---")

        # 1. Replication Padding
        # We append the last 3 characters of the message to itself.
        # If message is shorter than 3, we repeat the whole message.
        padding_len = 3
        if len(plaintext) < padding_len:
            suffix = plaintext
        else:
            suffix = plaintext[-padding_len:]

        padded_text = plaintext + suffix
        print(f"1. Padding Applied: '{padded_text}' (Replicated '{suffix}')")

        # 2. Convert Padded Text to Integer (m)
        m = self._text_to_int(padded_text)
        print(f"2. Converted to Integer (m): {m}")

        # 3. Plaintext Check (Constraint Check)
        if m >= self.n:
            print("\n[ERROR] Message too large!")
            print(f"Message value (m): {m}")
            print(f"Public Key (n):    {self.n}")
            print("The message (plus padding) results in a number larger than n.")
            print("In a real system, we would split this into blocks.")
            return None

        print("3. Size Check: OK (m < n)")

        # 4. Encryption: c = m^2 mod n
        c = pow(m, 2, self.n)

        print(f"4. Encryption (c = m^2 mod n)")
        return c

    def getPrivateKeys(self):
        return self._p, self._q




#---- Decryption --------------------------------------------------------------------


    def _int_to_text(self, x):
        """
        Converts integer back to text using Base-27 decoding.
        This reverses _text_to_int().
        """
        result = []
        while x > 0:
            x, r = divmod(x, 27)
            result.append(self.alphabet[r])

        return ''.join(reversed(result))


    def _crt(self, ap, aq):
        """
        Solve CRT system:
            x = ap (mod p)
            x = aq (mod q)
        """
        p, q = self._p, self._q
        n = self.n

        Np = q
        Nq = p

        # inverses
        invNp = pow(Np, -1, p)
        invNq = pow(Nq, -1, q)


        x = (ap * Np * invNp + aq * Nq * invNq) % n
        return x

    def decrypt(self, c):
        """
        Rabin decryption with redundancy recovery.
        Selects the root whose text ends with the replicated characters.
        """

        print("\n========================")
        print("      DECRYPTION")
        print("========================")
        print(f"Ciphertext (c): {c}")
        print(f"Using private keys p={self._p}, q={self._q}")
        print(f"Modulus n = p*q = {self.n}\n")

        if self._p is None or self._q is None:
            raise Exception("Private keys not available.")

        p, q = self._p, self._q
        n = self.n

        # -----------------------------------------
        # Step 0: Ciphertext Validation
        # -----------------------------------------
        print("Step 0: Validating ciphertext...")

        # Check c < n
        if c >= n:
            print("   Ciphertext is not in Zn (must satisfy c < n).")
            raise ValueError("Invalid ciphertext: c must be < n.")
        else:
            print("  Ciphertext is within valid range (c < n).")

        # Check Legendre symbols (must be quadratic residue modulo p and q)
        leg_p = pow(c, (p - 1) // 2, p)
        leg_q = pow(c, (q - 1) // 2, q)

        print(f"  Legendre symbol (c | p) = {leg_p}")
        print(f"  Legendre symbol (c | q) = {leg_q}")

        if leg_p != 1 or leg_q != 1:
            print("   Ciphertext is NOT a quadratic residue modulo p or q.")
            raise ValueError("Invalid ciphertext: not a quadratic residue.")
        else:
            print("   Ciphertext is a valid quadratic residue under both p and q.\n")

        # -----------------------------------------
        # Step 1: Square roots mod p and mod q
        # -----------------------------------------
        print("Step 1: Computing square roots modulo p and q...")
        r_p = pow(c, (p + 1) // 4, p)
        r_q = pow(c, (q + 1) // 4, q)
        print(f"  √c mod p = ±{r_p} (mod {p})")
        print(f"  √c mod q = ±{r_q} (mod {q})\n")

        roots = []

        # -----------------------------------------
        # Step 2: 4 CRT combinations
        # -----------------------------------------
        print("Step 2: Building 4 CRT combinations...")
        combos = [
            ( r_p,  r_q),
            ( r_p, -r_q % q),
            (-r_p % p,  r_q),
            (-r_p % p, -r_q % q)
        ]

        labels = ["(+,+)", "(+,-)", "(-,+)", "(-,-)"]

        for idx, (a_p, a_q) in enumerate(combos):
            print(f"  Combination {labels[idx]}:")
            print(f"    ap = {a_p} (mod p)")
            print(f"    aq = {a_q} (mod q)")
            root = self._crt(a_p, a_q)
            print(f"    -> CRT root = {root}\n")
            roots.append(root)

        # -----------------------------------------
        # Step 3: Redundancy check
        # -----------------------------------------
        print("Step 3: Checking redundancy on decoded plaintexts...")

        candidates = []

        for i, r in enumerate(roots):
            text = self._int_to_text(r)
            print(f"  Root {i+1}: {r}")
            print(f"    Decoded text: '{text}'")

            if len(text) < 6:
                print("    Too short to contain redundancy.\n")
                continue

            if text[-3:] == text[-6:-3]:
                print("    Redundancy OK (last 3 chars match previous 3)")
                print(f"      Accepted plaintext before trimming: '{text}'")
                cleaned = text[:-3]
                print(f"      Final cleaned plaintext: '{cleaned}'\n")
                candidates.append(cleaned)
            else:
                print("     Redundancy check failed.\n")

        if not candidates:
            print("\n!!! ERROR: No valid root matches redundancy !!!\n")
            raise ValueError("No valid root found (redundancy mismatch).")

        print("========================")
        print("Decryption successful!")
        print("========================\n")

        return candidates[0]


# --- Usage Example ---

if __name__ == "__main__":
    # Using smaller keys for demonstration readability
    rabin = RabinEncryptor(key_size_bits=128)

    # Generate Keys
    rabin.generate_keys()

    # Example 1: A short message that fits
    msg1 = "hello world"
    cipher1 = rabin.encrypt(msg1)
    if cipher1:
        print(f"Ciphertext: {cipher1}")
        print(f"Private Keys: {rabin.getPrivateKeys()}")

        # --- DECRYPTION ---
        print("\n--- Decrypting ---")
        plain1 = rabin.decrypt(cipher1)
        print(f"Recovered Plaintext: '{plain1}'\n")

    # Example 2: A message that might be too long for this key size
    msg2 = "this message is way too long to fit inside a small key like this"
    cipher2 = rabin.encrypt(msg2)
    if cipher2:
        print(f"Ciphertext: {cipher2}")
        print(f"Private Keys: {rabin.getPrivateKeys()}")

        # --- DECRYPTION ---
        print("\n--- Decrypting ---")
        plain2 = rabin.decrypt(cipher2)
        print(f"Recovered Plaintext: '{plain2}'\n")
