#include <unistd.h>
#include <iostream>
int main() {
    char* tty = ttyname(STDIN_FILENO);
    if (!tty) return 1;
    std::cout << tty << '\n';
}
