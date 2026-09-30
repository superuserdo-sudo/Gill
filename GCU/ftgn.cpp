#include <iostream>
int main(int argc, char** argv) {
    if (argc < 2) return 1;
    long long n = std::stoll(argv[1]);
    std::cout << n << '\n';
}
