#include <iostream>
#include <filesystem>
int main(int argc, char** argv) {
    if (argc < 2) return 1;
    std::cout << std::filesystem::path(argv[1]).parent_path().string() << '\n';
}
