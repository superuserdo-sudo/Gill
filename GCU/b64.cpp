#include <iostream>
int main() {
    const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    unsigned char a,b,c;
    while (std::cin.read(reinterpret_cast<char*>(&a),1)) {
        if (!std::cin.read(reinterpret_cast<char*>(&b),1)) {
            std::cout << table[a>>2] << table[(a&3)<<4] << "==\n"; break;
        }
        std::cout << table[a>>2] << table[((a&3)<<4)|(b>>4)];
        if (!std::cin.read(reinterpret_cast<char*>(&c),1)) {
            std::cout << table[(b&15)<<2] << "=\n"; break;
        }
        std::cout << table[((b&15)<<2)|(c>>6)] << table[c&63];
    }
}
