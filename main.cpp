#include <iostream>
#include <fstream>
#include <boost/multiprecision/cpp_int.hpp>
#include "./functions.hpp"

using namespace std;
using namespace boost::multiprecision;

// shortcut for veeery big number (1024 bits)
typedef number<cpp_int_backend<1024, 1024, unsigned_magnitude, unchecked, void>> BigInt;

int main() {

    // read file - full ASCII
    string text = readFile("input.txt");
    cout << "text: " << text << endl;

    return 0;
}