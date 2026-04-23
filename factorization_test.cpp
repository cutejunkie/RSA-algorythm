#include <iostream>
#include <chrono>
#include "./functions.hpp"

using namespace std;
using namespace boost::multiprecision;

typedef number<
    cpp_int_backend<
        1024,
        1024,
        unsigned_magnitude,
        unchecked,
        void
    >
> BigInt;

int main() {

    vector<int> bitSizes = {
        32,
        40,
        48,
        56,
        64,
        72,
        80,
        88
    };

    for (int bits : bitSizes) {

        cout << "\n=====================\n";
        cout << bits << " BIT RSA\n";

        BigInt p = generatePrime(bits / 2);
        BigInt q = generatePrime(bits / 2);

        BigInt n = p * q;

        cout << "n = " << n << endl;

        BigInt fp, fq;
        long long iterations = 0;

        auto start = chrono::high_resolution_clock::now();

        bool success = factorize(n, fp, fq, iterations);

        auto end = chrono::high_resolution_clock::now();

        auto duration =
            chrono::duration_cast<chrono::milliseconds>(
                end - start
            );

        cout << "Time: "
             << duration.count()
             << " ms\n";

        cout << "Iterations: "
             << iterations
             << endl;

        if (success) {
            cout << "SUCCESS\n";

            cout << "p = "
                 << fp
                 << endl;

            cout << "q = "
                 << fq
                 << endl;
        }
        else {
            cout << "FAILED\n";
        }
    }

    return 0;
}