#include <iostream>
#include <fstream>
#include <boost/multiprecision/cpp_int.hpp>
#include "./functions.hpp"

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/integer.hpp> // Tutaj siedzi gcdext i invert

namespace mp = boost::multiprecision;

// Twoja definicja
typedef mp::number<mp::cpp_int_backend<1024, 1024, mp::unsigned_magnitude, mp::unchecked, void>> BigInt;
using namespace std;
using namespace boost::multiprecision;

// shortcut for veeery big number (1024 bits)
typedef number<cpp_int_backend<1024, 1024, unsigned_magnitude, unchecked, void>> BigInt;

int main() {
    // read file - full ASCII
    string text = readFile("input.txt");
    cout << "text: " << text << endl;

    // step4 - keys
    BigInt p("298834810371436605210040030113074317611");
    BigInt q("235131813645022530117462002306283236741");
    BigInt n = p * q;
    BigInt phi = (p - 1) * (q - 1);
    BigInt e = 65537;
    
    // 3 result to bigint
    BigInt d = calculate_d(e, phi);


    // Przetwarzanie
    for (size_t i = 0; i < text.length(); i += 10) {
        string originalBlock = text.substr(i, 10);
        while (originalBlock.length() < 10) originalBlock += " ";

        BigInt m = step3_textToNumber(originalBlock);
        BigInt c = step5_encode(m, e, n);
        BigInt m2 = step6_decode(c, d, n);
        string decodedBlock = numberToText(m2);

        cout << "Blok: [" << originalBlock << "] -> ";
        if (originalBlock == decodedBlock) cout << "OK" << endl;
        else cout << "ERROR" << endl;
    }
    return 0;
}