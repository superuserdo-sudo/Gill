#include <iostream>
#include <filesystem>
int main() {
    for (const auto& e : std::filesystem::directory_iterator(".")) {
        auto size = e.is_regular_file() ? std::filesystem::file_size(e.path()) : 0;
        std::cout << size << '\t' << e.path().filename().string() << '\n';
    }
}
