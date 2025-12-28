#include <iostream>
#include <cmath>
#include <algorithm> 
#include <numeric>        
#include <chrono>         

using namespace std;

/*
 * Function: isPerfectSquare
 * -------------------------
 * Tests whether an integer x is a perfect square.
 *
 * Steps:
 *   1. Compute s = floor(sqrt(x)).
 *   2. Check whether s*s equals x exactly.
 *
 * Returns:
 *   true  if x is a perfect square
 *   false otherwise
 */
bool isPerfectSquare(long long x) {
    if (x < 0) return false;       
    long long s = sqrtl(x);
    return s * s == x;
}

/*
 * Function: generalizedFermat
 * ---------------------------
 * Implements the Generalized Fermat Factorization Algorithm.
 * Adds:
 *   - Full log output to "fermat_log.txt"
 *   - A global timeout of 15 seconds
 *
 * INPUT:
 *   n : odd composite integer (not a perfect square)
 *   B : bound for the inner loop over t
 *
 * OUTPUT:
 *   Returns a non-trivial factor of n.
 *   Returns -1 if timeout occurs.
 *
 * Algorithm:
 *   For k = 1, 2, 3, ...
 *       t0 = floor( sqrt(k*n) )
 *       For t = t0+1 ... t0+B
 *           Compute d = t^2 - k*n
 *           If d is a perfect square s^2:
 *               n = (1/k)(t - s)(t + s)
 *               Extract factors using gcd.
 *               STOP.
 */
long long generalizedFermat(long long n, long long B) {

    ofstream log("fermat_log.txt");
    log << "=== Generalized Fermat’s Algorithm Log ===\n\n";

    auto start = chrono::high_resolution_clock::now();
    const double TIMEOUT = 15.0;     // seconds

    for (long long k = 1; ; k++) {

        auto now = chrono::high_resolution_clock::now();
        double elapsed = chrono::duration<double>(now - start).count();
        if (elapsed >= TIMEOUT) {
            log << "\n*** TIMEOUT: Exceeded 15 seconds. Stopping. ***\n";
            log.close();
            return -1;
        }

        long long kn = k * n;          
        long long t0 = sqrtl(kn);       

        log << "\n----------------------------------------\n";
        log << "Trying k = " << k << "\n";
        log << "k * n = " << kn << "\n";
        log << "t0 = floor( sqrt(k*n) ) = " << t0 << "\n";
        log << "Testing t from " << (t0 + 1) << " to " << (t0 + B) << "\n";

        /*
         * Inner loop: search for t such that
         *      t^2 - k*n = perfect square
         */
        for (long long t = t0 + 1; t <= t0 + B; t++) {

            now = chrono::high_resolution_clock::now();
            elapsed = chrono::duration<double>(now - start).count();
            if (elapsed >= TIMEOUT) {
                log << "\n*** TIMEOUT: Exceeded 15 seconds. Stopping. ***\n";
                log.close();
                return -1;
            }

            long long diff = t * t - kn;    // Compute d = t^2 - k*n

            log << "  t = " << t
                << ", t^2 = " << (t * t)
                << ", t^2 - k*n = " << diff;

            // Check if diff is a perfect square
            if (isPerfectSquare(diff)) {
                long long s = sqrtl(diff);

                log << "  --> PERFECT SQUARE FOUND! (s = " << s << ")\n";

                /*
                 * When t^2 - k*n = s^2,
                 * we have:
                 *       (t - s)(t + s) = k*n
                 *
                 * n = (1/k)(t - s)(t + s)
                 * Possible factors:
                 *      factor1 = (t - s) / k
                 *      factor2 = (t + s)
                 */

                long long factor1 = (t - s) / k;
                long long factor2 = (t + s);

                log << "  (t - s) / k = " << factor1 << "\n";
                log << "  (t + s) = " << factor2 << "\n";

                // Use gcd to extract a non-trivial factor of n
                long long g = std::gcd(factor1, n);
                log << "  gcd(factor1, n) = " << g << "\n";

                if (g != 1 && g != n) {
                    log << "\n*** Non-trivial factor found from factor1! ***\n";
                    log.close();
                    return g;
                }

                // Try factor2
                g = std::gcd(factor2, n);
                log << "  gcd(factor2, n) = " << g << "\n";

                if (g != 1 && g != n) {
                    log << "\n*** Non-trivial factor found from factor2! ***\n";
                    log.close();
                    return g;
                }

                log << "  Perfect square found, but gcd did not produce a valid factor.\n";
            }
            else {
                log << "  (not a square)\n";
            }
        }

        // No t worked for this k, continue looping
        log << "No perfect squares found for k = " << k << ". Continuing...\n";
    }
}


int main() {
    long long n, B;

    cout << "Enter odd composite number n (not a square): ";
    cin >> n;

    cout << "Enter bound B: ";
    cin >> B;

    long long factor = generalizedFermat(n, B);

    cout << "\n========================================\n";

    if (factor == -1) {
        cout << "TIMEOUT: Algorithm exceeded 15 seconds.\n";
        cout << "See fermat_log.txt for details.\n";
    } else {
        cout << "Found non-trivial factor: " << factor << "\n";
        cout << "Other factor: " << n / factor << "\n";
    }

    cout << "Log written to fermat_log.txt\n";
    cout << "========================================\n";

    return 0;
}
