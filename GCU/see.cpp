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
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;
namespace fs = filesystem;

struct Item {
    fs::directory_entry e;
    string name;
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
    bool all=0, wt=0, full=0, bytime=0, bysize=0, rev=0;

    for (int i=1; i<argc; i++) {
        string x=argv[i];

        if (x=="-h" || x=="--help") {
            help();
            return 0;
        }

        if (x=="-vir") {
            cout<<"see 1.0.1\n";
            return 0;
        }

        if (x=="-a") all=1;
        else if (x=="-w") wt=1;
        else if (x=="-wt") wt=full=1;
        else if (x=="-t") bytime=1;
        else if (x=="-S") bysize=1;
        else if (x=="-r") rev=1;
    }

    vector<Item> v;

    for (auto& e : fs::directory_iterator(".")) {
        string n=e.path().filename();

        if (!all && !n.empty() && n[0]=='.')
            continue;

        v.push_back({e,n});
    }

    sort(v.begin(),v.end(),[](const Item& a,const Item& b) {
        return a.name < b.name;
    });

    if (rev)
        reverse(v.begin(),v.end());

    struct winsize ws{};
    ioctl(STDOUT_FILENO,TIOCGWINSZ,&ws);

    int width = ws.ws_col ? ws.ws_col : 80;
    int longest = 0;

    for (auto& x : v)
        longest = max(longest,(int)x.name.size());

    int col = longest + 3;
    int columns = max(1,width / col);
    int rows = (v.size() + columns - 1) / columns;

    for (int r=0; r<rows; r++) {
        for (int c=0; c<columns; c++) {
            int i = c * rows + r;

            if (i >= (int)v.size())
                continue;

            cout << color(v[i].e)
                 << left << setw(col)
                 << v[i].name
                 << "\033[0m";
        }

        cout << '\n';
    }
}
