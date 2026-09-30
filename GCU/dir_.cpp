#include <iostream>
#include <filesystem>
int main() {
    for (const auto& e : std::filesystem::directory_iterator("."))
        std::cout << e.path().filename().string() << '\n';
}
