#include "functions.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <random>


std::string readFile(std::string file_name) {
    std::string text;
    std::ifstream file(file_name);

    if (file.is_open()) {
        // read all from start to end
        text.assign((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());
        file.close();

    } else {
        std::cout << "warning: cannot open " << file_name << " will use default text\n";
        text = "test text RSA :>"; 
    }

    return text;
}

std::string krok1_wczytaj(std::string file_name) {
    std::string text;
    std::ifstream file(file_name);
    if (file.is_open()) {
        text.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
    } else {
        std::cout << "Warning: file doesn't exist\n";
        text = "Standard text RSA.";
    }
    return text;
}

BigInt step3_textToNumber(std::string block) {
    BigInt m = 0;
    for (unsigned char c : block) {
        m = (m << 8) + c;
    }
    return m;
}

std::string numberToText(BigInt m) {
    std::string text = "";
    for (int i = 0; i < 10; ++i) {
        text = (char)(m & 0xFF) + text;
        m >>= 8;
    }
    return text;
}

BigInt step5_encode(BigInt m, BigInt e, BigInt n) {
    return powm(m, e, n);
}

BigInt step6_decode(BigInt c, BigInt d, BigInt n) {
    return powm(c, d, n);
}

// Funkcja obliczająca odwrotność modularną (d) bez użycia gcdext z Boosta
BigInt calculate_d(BigInt e_val, BigInt phi_val) {
    cpp_int a = cpp_int(e_val);
    cpp_int b = cpp_int(phi_val);
    cpp_int m0 = b;
    cpp_int y = 0, x = 1;

    if (b == 1) return 0;

    while (a > 1) {
        // q to iloraz
        cpp_int q = a / b;
        cpp_int t = b;

        // b to reszta z dzielenia, standardowy Euklides
        b = a % b;
        a = t;
        t = y;

        // Aktualizacja x i y
        y = x - q * y;
        x = t;
    }

    // Upewniamy się, że x jest dodatnie
    if (x < 0) x += m0;

    return (BigInt)x;
}




BigInt generateRandomBigInt(int bits) {
    std::random_device rd;
    std::mt19937_64 gen(rd());

    BigInt result = 0;

    for (int i = 0; i < bits; i += 64) {
        result <<= 64;
        result += gen();
    }

    // ustaw najwyższy bit
    result |= (BigInt(1) << (bits - 1));

    // liczba nieparzysta
    result |= 1;

    return result;
}

bool isPrime(BigInt n, int iterations) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;

    BigInt d = n - 1;
    int s = 0;

    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    std::random_device rd;
    std::mt19937_64 gen(rd());

    for (int i = 0; i < iterations; i++) {
        BigInt a = 2 + gen() % (n - 3);

        BigInt x = powm(a, d, n);

        if (x == 1 || x == n - 1)
            continue;

        bool passed = false;

        for (int r = 1; r < s; r++) {
            x = powm(x, 2, n);

            if (x == n - 1) {
                passed = true;
                break;
            }
        }

        if (!passed)
            return false;
    }

    return true;
}

BigInt generatePrime(int bits) {
    while (true) {
        BigInt candidate = generateRandomBigInt(bits);

        if (isPrime(candidate))
            return candidate;
    }
}