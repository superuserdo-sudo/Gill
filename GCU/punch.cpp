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
#include <sys/stat.h>
#include <utime.h>
#include <ctime>
#include <cstring>
using namespace std;
namespace fs=filesystem;

void help(){
    cout<<"punch 1.0.1\n"
        <<"-acct=TIME       access time\n"
        <<"-modtime=TIME    modification time\n"
        <<"-mtime=TIME      modification time\n"
        <<"-dcide           don't create\n"
        <<"-dc              don't create\n"
        <<"-tot=FILE        take other's time\n"
        <<"-ttstam=TIME     take this timestamp\n"
        <<"-date=TIME       set date\n"
        <<"-help            show help\n"
        <<"-vir             show version\n";
}

time_t gettime(string s){
    tm t{};
    if(sscanf(s.c_str(),"%d-%d-%d %d:%d:%d",
        &t.tm_year,&t.tm_mon,&t.tm_mday,
        &t.tm_hour,&t.tm_min,&t.tm_sec)!=6) return -1;
    t.tm_year-=1900;
    t.tm_mon--;
    return mktime(&t);
}

int main(int c,char**v){
    string at,mt,other,date;
    bool dc=0;

    for(int i=1;i<c;i++){
        string x=v[i];

        if(x=="-help") return help(),0;
        if(x=="-vir") return cout<<"punch 1.0.1\n",0;
        if(x=="-dc"||x=="-dcide") dc=1;
        else if(x.rfind("-acct=",0)==0) at=x.substr(6);
        else if(x.rfind("-modtime=",0)==0) mt=x.substr(9);
        else if(x.rfind("-mtime=",0)==0) mt=x.substr(7);
        else if(x.rfind("-tot=",0)==0) other=x.substr(5);
        else if(x.rfind("-ttstam=",0)==0) date=x.substr(8);
        else if(x.rfind("-date=",0)==0) date=x.substr(6);
    }

    for(int i=1;i<c;i++){
        string x=v[i];
        if(x[0]=='-') continue;

        if(!fs::exists(x)){
            if(dc) continue;
            ofstream(x).close();
        }

        utimbuf u{};
        u.actime=time(nullptr);
        u.modtime=u.actime;

        if(!at.empty()){
            time_t t=gettime(at);
            if(t!=-1) u.actime=t;
        }

        if(!mt.empty()||!date.empty()){
            time_t t=gettime(!mt.empty()?mt:date);
            if(t!=-1) u.modtime=t;
        }

        if(!other.empty()){
            struct stat s{};
            if(stat(other.c_str(),&s)==0){
                u.actime=s.st_atime;
                u.modtime=s.st_mtime;
            }
        }

        if(utime(x.c_str(),&u)!=0)
            cerr<<"punch: "<<x<<": "<<strerror(errno)<<"\n";
    }
}
