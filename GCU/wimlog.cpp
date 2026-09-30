#include <unistd.h>
#include <iostream>
int main() {
    char* name = getlogin();
    if (!name) return 1;
    std::cout << name << '\n';
}
