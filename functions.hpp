#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
#include <boost/multiprecision/cpp_int.hpp>

// type definition
using namespace boost::multiprecision;
typedef number<cpp_int_backend<1024, 1024, unsigned_magnitude, unchecked, void>> BigInt;

// Reads text from provided file
std::string readFile(std::string file_name);
BigInt step3_textToNumber(std::string block);
std::string numberToText(BigInt m);
BigInt step5_encode(BigInt m, BigInt e, BigInt n);
BigInt step6_decode(BigInt c, BigInt d, BigInt n);
BigInt calculate_d(BigInt e_val, BigInt phi_val);

BigInt generateRandomBigInt(int bits);
bool isPrime(BigInt n, int iterations = 20);
BigInt generatePrime(int bits);

#endif