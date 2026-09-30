#include <fstream>
#include <filesystem>
int main(int c,char**v){
    if(c<2)return 1;
    std::ofstream(v[1],std::ios::app).close();
    std::filesystem::last_write_time(v[1],std::filesystem::file_time_type::clock::now());
}
