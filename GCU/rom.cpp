// VIR: 1.0.1
// GCU tool. License: GOSL.
// Copyright © Gill Open Source Project (GOSP), 2026
//
// rom tool: it is a removeing tool for gill/sel4 os
//
// Everyone can change the code, add, delete, and modify it
// Please give credit
//
// Thanks to Rayan Abdelli (Founder),
// also known on GitHub as "superuserdo-sudo"
#include <iostream>
#include <filesystem>
using namespace std;
namespace fs = filesystem;

void help(){
    cout<<"rom [options] <file...>\n\n"
        <<"-frc, --force                    Force delete\n"
        <<"-dwa, --delete-without-asking   Delete without asking\n"
        <<"-swad, --showme-what-am-deleteing Show what will be deleted\n"
        <<"-h, --help                      Show help\n";
}

int main(int c,char**v){
    bool force=0,dwa=0,show=0;
    for(int i=1;i<c;i++){
        string x=v[i];
        if(x=="-h"||x=="--help") return help(),0;
        if(x=="-frc"||x=="--force") force=1;
        else if(x=="-dwa"||x=="--delete-without-asking") dwa=1;
        else if(x=="-swad"||x=="--showme-what-am-deleteing") show=1;
    }

    for(int i=1;i<c;i++){
        string x=v[i];
        if(x[0]=='-') continue;

        fs::path p=x;
        if(!fs::exists(p)){
            cerr<<"rom: "<<x<<": not found\n";
            continue;
        }

        if(show) cout<<"Deleting: "<<p<<"\n";

        if(!dwa){
            cout<<"Delete "<<p<<"? [y/N] ";
            char a; cin>>a;
            if(a!='y'&&a!='Y') continue;
        }

        error_code e;
        if(fs::is_directory(p))
            fs::remove_all(p,e);
        else
            fs::remove(p,e);

        if(e && force){
            cerr<<"rom: "<<x<<": "<<e.message()<<"\n";
            continue;
        }
        if(e) cerr<<"rom: "<<x<<": "<<e.message()<<"\n";
    }
}
