#include <iostream>
#include <filesystem>
int main(){
    for(auto& x: std::filesystem::directory_iterator("."))
        std::cout << x.path().filename().string() << '\n';
}
