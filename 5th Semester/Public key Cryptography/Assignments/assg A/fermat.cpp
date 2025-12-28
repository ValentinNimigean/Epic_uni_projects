#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

bool isPerfectSquare(long long x) {
    if (x < 0) return false;
    long long s = sqrtl(x);
    return s * s == x;
}

int main() {
    long long n, B;

    cout << "Enter n (odd composite, not a square): ";
    cin >> n;
    cout << "Enter bound B: ";
    cin >> B;

    ofstream log("fermat_log.txt");
    log << "=== Fermat Factorization Log ===\n\n";

    long long t0 = sqrtl(n);

    cout << "\nInitialization:\n";
    cout << "t0 = floor(sqrt(n)) = " << t0 << "\n\n";

    log << "Initialization:\n";
    log << "t0 = floor(sqrt(n)) = " << t0 << "\n\n";

    cout << "Iterations:\n\n";
    log << "Iterations:\n\n";

    long long found_t = -1, found_s = -1;

    for (long long k = 1; k <= B; k++) {
        long long t = t0 + k;
        long long diff = t * t - n;

        bool square = isPerfectSquare(diff);

        cout << "t = t0 + " << k << ":   t^2 - n = "
             << diff << "     perfect square (yes/no): "
             << (square ? "yes" : "no") << "\n";

        log << "t = t0 + " << k << ":   t^2 - n = "
            << diff << "     perfect square (yes/no): "
            << (square ? "yes" : "no") << "\n";

        if (square) {
            long long s = sqrtl(diff);
            found_t = t;
            found_s = s;
            break;
        }
    }

    if (found_t == -1) {
        cout << "\nNo perfect square found within bound.\n";
        log << "\nNo perfect square found within bound.\n";
        log.close();
        return 0;
    }

    cout << "\nValues:\n";
    cout << "s = " << found_s << "\n";
    cout << "t = " << found_t << "\n\n";

    log << "\nValues:\n";
    log << "s = " << found_s << "\n";
    log << "t = " << found_t << "\n\n";

    long long a = found_t - found_s;
    long long b = found_t + found_s;

    if (a > b) swap(a, b);

    cout << "Conclusion:\n";
    cout << "The obtained two factors of n are (in increasing order): "
         << a << " and " << b << ".\n";

    log << "Conclusion:\n";
    log << "The obtained two factors of n are (in increasing order): "
        << a << " and " << b << ".\n";

    log.close();

    cout << "\nLog written to fermat_log.txt\n";

    return 0;
}
