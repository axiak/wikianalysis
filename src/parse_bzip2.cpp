#include <iostream>
#include <fstream>
#include <re2.h>

using namespace std;
using namespace re2;

RE2 textstart("<text[^>]+>");
RE2 title("<title>(.+?)</title>");
RE2 id("<id>(.*?)</id>");

int main(int argc, char**argv)
{
    ofstream adj_file("./wp_adjlist.dat", ios::out | ios::trunc),
        id_map("./wp_idmap.dat", ios::out | ios::trunc);

    return 0;
}
