#include <filesystem>
int main(int argc, char** argv) {
    if (argc < 3) return 1;
    try {
        std::filesystem::copy(argv[1], argv[2],
            std::filesystem::copy_options::recursive |
            std::filesystem::copy_options::overwrite_existing);
        return 0;
    } catch (...) { return 1; }
}
