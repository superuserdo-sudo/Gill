#include <filesystem>
#include <string>
int main(int argc, char** argv) {
    if (argc != 3) return 1;
    std::filesystem::path p = argv[2];
    if (std::string(argv[1]) == "-e") return std::filesystem::exists(p) ? 0 : 1;
    if (std::string(argv[1]) == "-f") return std::filesystem::is_regular_file(p) ? 0 : 1;
    if (std::string(argv[1]) == "-d") return std::filesystem::is_directory(p) ? 0 : 1;
    return 1;
}
