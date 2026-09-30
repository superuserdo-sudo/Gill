#include <sys/utsname.h>
#include <iostream>
int main() {
    utsname u{};
    if (uname(&u) != 0) return 1;
    std::cout << u.machine << '\n';
}
