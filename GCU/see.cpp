// VIR: 1.0.1
// GCU tool. License: GOSL.
// Copyright © Gill Open Source Project (GOSP), 2026
//
// see tool: a file listing tool for Gill/SeL4 OS
//
// Everyone can change the code, add, delete, and modify it
// Please give credit
//
// Thanks to Rayan Abdelli (Founder),
// also known on GitHub as "superuserdo-sudo"
#include <isoterm>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <unistd.h>
using namespace std;
namespace fs = filesystem;

int main(int c,char**v){
    bool a=0,w=0,t=0,S=0,r=0;
    for(int i=1;i<c;i++){
        string o=v[i];
        if(o=="-wt") w=1;
        else for(char x:o.substr(1)){
            if(x=='a') a=1;
            if(x=='w') w=1;
            if(x=='t') t=1;
            if(x=='S') S=1;
            if(x=='r') r=1;
        }
    }

    vector<fs::directory_entry> f;
    for(auto&e:fs::directory_iterator("."))
        if(a||e.path().filename().string()[0]!='.')
            f.push_back(e);

    sort(f.begin(),f.end(),[&](auto&A,auto&B){
        if(t)return A.last_write_time()>B.last_write_time();
        if(S)return A.file_size()>B.file_size();
        return A.path().filename()<B.path().filename();
    });

    if(r) reverse(f.begin(),f.end());

    for(auto&e:f){
        string n=e.path().filename().string(),c="\033[0m";
        if(e.is_directory()) c="\033[34m";
        else if(e.is_symlink()) c="\033[35m";
        else if(access(e.path().c_str(),X_OK)==0) c="\033[32m";
        else if(e.path().extension()==".cpp"||
                e.path().extension()==".c"||
                e.path().extension()==".h") c="\033[36m";

        cout<<c<<n<<"\033[0m";
        if(e.is_directory()) cout<<"/";
        if(w) cout<<"  "<<e.last_write_time().time_since_epoch().count();
        cout<<"\n";
    }
}
