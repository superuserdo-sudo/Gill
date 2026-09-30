#include <unistd.h>
#include <iostream>
#include <vector>
int main() {
    int n = getgroups(0,nullptr);
    if (n < 0) return 1;
    std::vector<gid_t> groups(n);
    if (getgroups(n,groups.data()) < 0) return 1;
    for (gid_t g : groups) std::cout << g << ' ';
    std::cout << '\n';
}
