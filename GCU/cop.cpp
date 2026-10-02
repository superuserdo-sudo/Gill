// VIR: 1.0.1
// GCU tool. License: GOSL.
// Copyright © Gill Open Source Project (GOSP), 2026
//
// cop tool: a file copy tool for Gill/SeL4 OS
//
// Everyone can change the code, add, delete, and modify it
// Please give credit
//
// Thanks to Rayan Abdelli (Founder),
// also known on GitHub as "superuserdo-sudo"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;
namespace fs = filesystem;

void help() {
    cout << "cop 1.0.1\n"
         << "Usage: cop [options] <source> <destination>\n\n"
         << "-rec       recursive\n"
         << "-arc       archive\n"
         << "-frc       force\n"
         << "-owrite    overwrite\n"
         << "-dr        don't replace\n"
         << "-oin       only if new\n"
         << "-swd       show what is copied\n"
         << "-bakup     backup\n"
         << "-hardlink  hard link\n"
         << "-sylink    symbolic link\n"
         << "-dsylink   don't symlink\n"
         << "-h         help\n"
         << "-vir       version\n";
}

bool newer(const fs::path& a, const fs::path& b) {
    return fs::last_write_time(a) > fs::last_write_time(b);
}

int main(int argc, char** argv) {
    bool rec = false, arc = false, frc = false;
    bool owrite = false, dr = false, oin = false;
    bool swd = false, bakup = false;
    bool hard = false, sy = false, dsy = false;

    string src, dst;

    for (int i = 1; i < argc; i++) {
        string x = argv[i];

        if (x == "-h") return help(), 0;
        if (x == "-vir") return cout << "cop 1.0.1\n", 0;

        if (x == "-rec") rec = true;
        else if (x == "-arc") arc = true;
        else if (x == "-frc") frc = true;
        else if (x == "-owrite") owrite = true;
        else if (x == "-dr") dr = true;
        else if (x == "-oin") oin = true;
        else if (x == "-swd") swd = true;
        else if (x == "-bakup") bakup = true;
        else if (x == "-hardlink") hard = true;
        else if (x == "-sylink") sy = true;
        else if (x == "-dsylink") dsy = true;
        else if (x[0] != '-') {
            if (src.empty()) src = x;
            else if (dst.empty()) dst = x;
        }
    }

    if (src.empty() || dst.empty()) {
        cerr << "cop: source and destination required\n";
        return 1;
    }

    fs::path s = src;
    fs::path d = dst;

    if (!fs::exists(s)) {
        cerr << "cop: " << src << ": not found\n";
        return 1;
    }

    // Hard link
    if (hard) {
        error_code e;
        fs::create_hard_link(s, d, e);
        if (e) {
            cerr << "cop: " << e.message() << '\n';
            return 1;
        }
        if (swd) cout << "Copied: " << s << " -> " << d << '\n';
        return 0;
    }

    // Symbolic link
    if (sy && !dsy) {
        error_code e;
        fs::create_symlink(s, d, e);
        if (e) {
            cerr << "cop: " << e.message() << '\n';
            return 1;
        }
        if (swd) cout << "Linked: " << s << " -> " << d << '\n';
        return 0;
    }

    // Don't replace
    if (fs::exists(d) && dr)
        return 0;

    // Only if source is newer
    if (fs::exists(d) && oin && !newer(s, d))
        return 0;

    // Backup
    if (fs::exists(d) && bakup) {
        fs::path backup = d;
        backup += ".bak";

        error_code e;
        fs::copy(d, backup,
                 fs::copy_options::recursive |
                 fs::copy_options::overwrite_existing, e);

        if (e) {
            cerr << "cop: backup: " << e.message() << '\n';
            return 1;
        }
    }

    fs::copy_options opt = fs::copy_options::none;

    if (rec || fs::is_directory(s))
        opt |= fs::copy_options::recursive;

    if (arc)
        opt |= fs::copy_options::copy_symlinks;

    if (owrite || frc)
        opt |= fs::copy_options::overwrite_existing;

    if (fs::exists(d) && !owrite && !frc && !dr && !oin) {
        cerr << "cop: destination exists: " << d << '\n';
        cerr << "Use -owrite to replace it.\n";
        return 1;
    }

    error_code e;
    fs::copy(s, d, opt, e);

    if (e) {
        cerr << "cop: " << e.message() << '\n';
        return 1;
    }

    if (swd)
        cout << "Copied: " << s << " -> " << d << '\n';

    return 0;
}
