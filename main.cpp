#include <iostream>
#include <fstream>
#include <boost/multiprecision/cpp_int.hpp>
#include "./functions.hpp"

using namespace std;
using namespace boost::multiprecision;

// shortcut for veeery big number (1024 bits)
typedef number<cpp_int_backend<1024, 1024, unsigned_magnitude, unchecked, void>> BigInt;

int main() {

    string text = readFile("input.txt");
    cout << text;

    if (text.length() == 0) {
        cout << "BLAD: Nic nie wczytano!" << endl;
        return 1;
    }

    return 0;
}