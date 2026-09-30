#include <iostream>
#include <iomanip>
int main() {
    unsigned char c;
    while (std::cin.read(reinterpret_cast<char*>(&c),1))
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << static_cast<int>(c) << ' ';
    std::cout << '\n';
}
