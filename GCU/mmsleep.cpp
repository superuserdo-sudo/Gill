#include <thread>
#include <chrono>
int main(int argc, char** argv) {
    if (argc < 2) return 1;
    std::this_thread::sleep_for(std::chrono::seconds(std::stoll(argv[1])));
}
