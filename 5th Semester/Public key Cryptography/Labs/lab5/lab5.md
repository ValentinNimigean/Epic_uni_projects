# Paillier Cryptosystem Documentation

The **Paillier cryptosystem** is an asymmetric public-key encryption scheme invented by Pascal Paillier in 1999. Its defining characteristic is that it is **additively homomorphic**, allowing computations to be performed on encrypted data without needing to decrypt it first.



## Key Components

### 1. The Public Key: `(n, g)`
The Public Key is used for **Encryption** and **Homomorphic Operations**.
* **$n$ (Modulus):** The product of two large secret primes ($p \times q$).
* **$g$ (Generator):** A value that "carries" the message into the encrypted space.

### 2. The Private Key: `(λ, μ)`
The Private Key is used for **Decryption**.
* **$\lambda$ (Lambda):** The secret exponent ($\text{lcm}(p-1, q-1)$).
* **$\mu$ (Mu):** The modular multiplicative inverse used as a correction factor.

## Mathematical Formulas

### A. Key Generation
1.  Choose two large primes $p$ and $q$.
2.  Compute $n = pq$ and $n^2$.
3.  Compute $\lambda = \text{lcm}(p-1, q-1)$.
4.  Select generator g - randomly generated value that respects properties (modular inverse exists for L(g^lambda mod n^2) mod n).
5.  Compute the modular inverse:
    $$\mu = (L(g^\lambda \pmod{n^2}))^{-1} \pmod n$$
    *Where the $L$-function is defined as:* $L(u) = \frac{u - 1}{n}$

### B. Encryption
To encrypt a message $m$ ($0 \le m < n$):
1.  Select a random integer $r$ - gcd(n,r)=1 so the property $(r^n)^\lambda \equiv 1 \pmod{n^2}$ holds.
2.  Compute the ciphertext $c$:
    $$c = g^m \cdot r^n \pmod{n^2}$$
    *Note: $g^m$ is the "signal" and $r^n$ is the "blinding noise".*

### C. Decryption
To recover the original message $m$:
1.  Compute the intermediate value $u$:
    $$u = c^\lambda \pmod{n^2}$$
2.  Extract the message using the $L$-function and $\mu$:
    $$m = L(u) \cdot \mu \pmod n$$

## Homomorphic Properties

The Paillier system allows specific math directly on ciphertexts:

| Operation | Ciphertext Math | Resulting Plaintext |
| :--- | :--- | :--- |
| **Addition** | $c_1 \cdot c_2 \pmod{n^2}$ | $m_1 + m_2 \pmod n$ |
| **Scalar Multiplication** | $c^k \pmod{n^2}$ | $k \cdot m \pmod n$ |


##  Variables Dictionary

| Variable | Name | Status | Description |
| :--- | :--- | :--- | :--- |
| $p, q$ | Primes | **Secret** | The original prime factors of $n$. |
| $n$ | Modulus | **Public** | Defines the message space boundary. |
| $g$ | Generator | **Public** | Encodes the message into an exponent. |
| $r$ | Random Factor | **Secret** | Ensures the same message looks different every time. |
| $\lambda$ | Lambda | **Private** | The secret exponent that deletes the random noise. |
| $\mu$ | Mu | **Private** | Cancels out the scaling of the generator. |
| $m$ | Plaintext | **Secret** | The original message (human-readable integer). |
| $c$ | Ciphertext | **Public** | The encrypted data (massive integer). |

