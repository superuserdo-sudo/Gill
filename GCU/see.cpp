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
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;
namespace fs = filesystem;

struct Item {
    fs::directory_entry e;
    string name;
    long long size;
    time_t time;
    bool dir;
};

void help() {
    cout << "see 1.0.1\n"
         << "Usage: see [options]\n\n"
         << "-a    show hidden files\n"
         << "-w    show time\n"
         << "-wt   show date and time\n"
         << "-t    sort by time\n"
         << "-S    sort by size\n"
         << "-r    reverse\n"
         << "-h    help\n"
         << "-vir  version\n";
}

string color(const fs::directory_entry& e) {
    if (e.is_directory()) return "\033[1;34m";
    if (e.is_symlink())  return "\033[1;35m";

    auto p = e.status().permissions();

    if ((p & fs::perms::owner_exec) != fs::perms::none)
        return "\033[1;32m";

    string x = e.path().extension();

    if (x == ".cpp" || x == ".c" || x == ".h")
        return "\033[1;36m";

    return "\033[0m";
}

int main(int argc, char** argv) {
    bool all=0, show=0, full=0, bytime=0, bysize=0, rev=0;

    for (int i=1; i<argc; i++) {
        string x=argv[i];

        if (x=="-h" || x=="--help") {
            help();
            return 0;
        }

        if (x=="-vir") {
            cout << "see 1.0.1\n";
            return 0;
        }

        if (x=="-a") all=1;
        else if (x=="-w") show=1;
        else if (x=="-wt") show=full=1;
        else if (x=="-t") bytime=1;
        else if (x=="-S") bysize=1;
        else if (x=="-r") rev=1;
    }

    vector<Item> v;

    for (auto& e : fs::directory_iterator(".")) {
        string n=e.path().filename();

        if (!all && !n.empty() && n[0]=='.')
            continue;

        long long size=0;

        if (e.is_regular_file())
            size=e.file_size();

        auto ft=e.last_write_time();
        auto now=chrono::system_clock::now();
        auto fnow=decltype(ft)::clock::now();

        time_t t=chrono::system_clock::to_time_t(
            now+(ft-fnow)
        );

        v.push_back({e,n,size,t,e.is_directory()});
    }

    sort(v.begin(),v.end(),[&](const Item& a,const Item& b) {
        if (a.dir != b.dir)
            return a.dir > b.dir;

        if (bytime && a.time != b.time)
            return a.time > b.time;

        if (bysize && a.size != b.size)
            return a.size > b.size;

        return a.name < b.name;
    });

    if (rev)
        std::reverse(v.begin(),v.end());

    struct winsize ws{};
    ioctl(STDOUT_FILENO,TIOCGWINSZ,&ws);

    int width=ws.ws_col ? ws.ws_col : 80;
    int longest=0;

    for (auto& x:v)
        longest=max(longest,(int)x.name.size());

    int col=longest+4;
    int columns=max(1,width/col);
    int rows=(v.size()+columns-1)/columns;

    for (int r=0;r<rows;r++) {
        for (int c=0;c<columns;c++) {
            int i=c*rows+r;

            if (i >= (int)v.size())
                continue;

            auto& x=v[i];

            cout << color(x.e) << left << x.name
                 << "\033[0m";

            if (show) {
                tm* tmv=localtime(&x.time);
                cout << " ";

                if (full)
                    cout << put_time(tmv,"%Y-%m-%d %H:%M");
                else
                    cout << put_time(tmv,"%H:%M");
            }

            if (c<columns-1)
                cout << setw(max(1,col-(int)x.name.size()-1));
        }

        cout << '\n';
    }
}
