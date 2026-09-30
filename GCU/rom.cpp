#include <filesystem>
int main(int argc, char** argv) {
    if (argc < 2) return 1;
    try { std::filesystem::remove_all(argv[1]); return 0; }
    catch (...) { return 1; }
}
