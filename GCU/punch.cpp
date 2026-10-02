// VIR: 1.0.1
// GCU tool. License: GOSL.
// Copyright © Gill Open Source Project (GOSP), 2026.
//
// punch tool: it is a file modify tool for Gill/SeL4 os
//
// Everyone can change the code, add, delete, and modify it.
// Please give credit.
//
// Thanks to Rayan Abdelli (Founder),
// also known on GitHub as "superuserdo-sudo".
#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <sstream>
using namespace std;
namespace fs=filesystem;

void help(){
    cout<<"punch 1.0.1\n"
        <<"-acct=TIME      access time\n"
        <<"-modtime=TIME   modification time\n"
        <<"-mtime=TIME     modification time\n"
        <<"-dcide          don't create\n"
        <<"-dc             don't create\n"
        <<"-tot=FILE       take other's time\n"
        <<"-ttstam=TIME    take this timestamp\n"
        <<"-date=TIME      set date\n"
        <<"-help           show help\n"
        <<"-vir            show version\n";
}

int main(int c,char**v){
    string at,mt,other,stamp,date;
    bool dc=0;

    for(int i=1;i<c;i++){
        string x=v[i];
        if(x=="-help") return help(),0;
        if(x=="-vir"){ cout<<"punch 1.0.1\n"; return 0; }
        if(x=="-dc"||x=="-dcide") dc=1;
        else if(x.rfind("-acct=",0)==0) at=x.substr(6);
        else if(x.rfind("-modtime=",0)==0) mt=x.substr(9);
        else if(x.rfind("-mtime=",0)==0) mt=x.substr(7);
        else if(x.rfind("-tot=",0)==0) other=x.substr(5);
        else if(x.rfind("-ttstam=",0)==0) stamp=x.substr(8);
        else if(x.rfind("-date=",0)==0) date=x.substr(6);
    }

    for(int i=1;i<c;i++){
        string x=v[i];
        if(x[0]=='-') continue;

        fs::path p=x;
        if(!fs::exists(p)){
            if(dc) continue;
            ofstream(p).close();
        }

        auto now=fs::file_time_type::clock::now();

        if(!other.empty() && fs::exists(other))
            now=fs::last_write_time(other);

        if(!stamp.empty() || !date.empty() || !mt.empty()){
            string s=!stamp.empty()?stamp:(!date.empty()?date:mt);
            tm t{};
            istringstream(s)>>get_time(&t,"%Y-%m-%d %H:%M:%S");
            if(!istringstream(s).fail()){
                time_t z=mktime(&t);
                now=fs::file_time_type::clock::from_sys(
                    chrono::system_clock::from_time_t(z));
            }
        }

        if(!at.empty()){
            // access-time support depends on the filesystem/platform
        }

        fs::last_write_time(p,now);
    }
}
