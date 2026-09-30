#include <filesystem>
int main(int argc, char** argv) {
    if (argc < 2) return 1;
    return std::filesystem::create_directory(argv[1]) ? 0 : 1;
}
