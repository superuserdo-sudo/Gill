#include <sys/utsname.h>
#include <iostream>
int main() {
    utsname u{};
    if (uname(&u) != 0) return 1;
    std::cout << u.sysname << ' ' << u.nodename << ' ' << u.release
              << ' ' << u.version << ' ' << u.machine << '\n';
}
