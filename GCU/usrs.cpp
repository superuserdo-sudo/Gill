#include <utmp.h>
#include <iostream>
int main() {
    setutent();
    while (auto* u = getutent())
        if (u->ut_type == USER_PROCESS) std::cout << u->ut_user << '\n';
    endutent();
}
