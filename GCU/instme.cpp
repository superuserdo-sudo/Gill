#include <filesystem>
int main(int argc, char** argv) {
    if (argc < 3) return 1;
    try {
        std::filesystem::copy_file(argv[1],argv[2],
            std::filesystem::copy_options::overwrite_existing);
        return 0;
    } catch (...) { return 1; }
}
