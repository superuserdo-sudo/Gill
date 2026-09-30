#include <iostream>
int main() {
    const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
    unsigned char c; int value = 0, bits = 0;
    while (std::cin.read(reinterpret_cast<char*>(&c), 1)) {
        value = (value << 8) | c; bits += 8;
        while (bits >= 5) { bits -= 5; std::cout << table[(value >> bits) & 31]; }
    }
    if (bits) std::cout << table[(value << (5 - bits)) & 31];
    std::cout << '\n';
}
