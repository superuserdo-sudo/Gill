#include <iostream>
#include <ctime>
int main() {
    std::time_t now = std::time(nullptr);
    std::cout << std::ctime(&now);
}
