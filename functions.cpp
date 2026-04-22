#include "functions.hpp"
#include <string>
#include <fstream>
#include <iostream>


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