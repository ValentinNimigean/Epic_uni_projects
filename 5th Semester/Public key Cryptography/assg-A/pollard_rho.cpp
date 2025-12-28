#include <iostream>
#include <cmath>
#include <numeric>   // std::gcd
#include <fstream>
#include <iomanip>   // setw

using namespace std;

// f(x) = x^2 + 1 (mod n)
long long f(long long x, long long n) {
    long long t = (x * x + 1) % n;
    return t;
}

int main() {
    long long n;
    int maxPairs;

    cout << "Enter odd composite number n: ";
    cin >> n;

    cout << "Enter number of iteration pairs to show (e.g. 10): ";
    cin >> maxPairs;

    ofstream log("pollard_rho_log.txt");

    if (!log) {
        cerr << "Error opening pollard_rho_log.txt for writing.\n";
        return 1;
    }

    // Header (console + log)
    cout << "Solution.\n\n";
    cout << "Iterations (results mod n):\n\n";

    log << "Solution.\n\n";
    log << "Iterations (results mod n):\n\n";

    // We need x0, x1, ..., x_{2*maxPairs}
    int maxIndex = 2 * maxPairs;
    long long *x = new long long[maxIndex + 1];

    x[0] = 2; // x0 = 2

    // Precompute all x_i = f(x_{i-1}) mod n
    for (int i = 1; i <= maxIndex; ++i) {
        x[i] = f(x[i - 1], n);
    }

    long long factor = -1;

    for (int j = 1; j <= maxPairs; ++j) {
        int idx1 = 2 * j - 1; // x_{2j-1}
        int idx2 = 2 * j;     // x_{2j}
        int idxSlow = j;      // x_j  (for gcd(|x_{2j} - x_j|, n))

        long long x1 = x[idx1];
        long long x2 = x[idx2];
        long long xSlow = x[idxSlow];

        long long diff = x2 - xSlow;
        if (diff < 0) diff = -diff;

        long long g = std::gcd(diff, n);

        // Build one line in the same style as the worksheet
        // x_{2j-1} = ...    x_{2j} = ...    (|x_{2j} - x_j|, n) = ...
        cout << "x" << idx1 << " = " << setw(5) << x1 << "    "
             << "x" << idx2 << " = " << setw(5) << x2 << "    "
             << "(|x" << idx2 << " - x" << idxSlow << "|, n) = "
             << g << "\n";

        log  << "x" << idx1 << " = " << setw(5) << x1 << "    "
             << "x" << idx2 << " = " << setw(5) << x2 << "    "
             << "(|x" << idx2 << " - x" << idxSlow << "|, n) = "
             << g << "\n";

        if (g > 1 && g < n && factor == -1) {
            factor = g;
            // we still print remaining pairs as 'x' if you want,
            // but the worksheet usually just leaves them blank/X.
            // Here we stop computing further gcds.
            break;
        }
    }

    cout << "\nConclusion:\n";
    log  << "\nConclusion:\n";

    if (factor == -1) {
        cout << "No non-trivial factor found with the given number of pairs.\n";
        log  << "No non-trivial factor found with the given number of pairs.\n";
    } else {
        long long other = n / factor;
        if (other < factor) std::swap(other, factor);

        cout << "The obtained two factors of n are (in increasing order): "
             << factor << " and " << other << ".\n";

        log  << "The obtained two factors of n are (in increasing order): "
             << factor << " and " << other << ".\n";
    }

    log.close();
    delete[] x;

    cout << "\nLog written to pollard_rho_log.txt\n";

    return 0;
}
