#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctype.h>
#include <re2.h>

using namespace std;
using namespace re2;

/* Regexes */
RE2 textstart_re("<text[^>]+>");
RE2 title_re("<title>(.+?)</title>");
RE2 id_re("<id>(\\d+)</id>");
RE2 link_re("\\[\\[(.+?)\\]\\]");

void inline normalize_link(string *link);

int main(int argc, char**argv)
{
    ofstream adj_file("./wp_adjlist.dat", ios::out | ios::trunc),
        id_map("./wp_idmap.dat", ios::out | ios::trunc);
    string line;
    long long id = 0;
    StringPiece *matches = new StringPiece[20];
    StringPiece sline;
    string current_title;
    bool in_text = false;

    while (!cin.eof()) {
        getline(cin, line);

        sline.set(line.c_str(), line.length());

        if (strncmp("  <page>", line.c_str(), 8) == 0) {
            in_text = false;
            id = 0;
            /* New page */
            getline(cin, line);
            sline.set(line.c_str(), line.length());
            if (title_re.Match(sline, 0, RE2::UNANCHORED, matches, 2)) {
                current_title = matches[1].as_string();
                normalize_link(&current_title);
            }
            else {
                continue;
            }
            getline(cin, line);
            sline.set(line.c_str(), line.length());
            if (id_re.Match(sline, 0, RE2::UNANCHORED, matches, 2)) {
                id = atol(matches[1].data());
                cout << current_title << ": " << id << endl;
            }
            else {
                continue;
            }
            id_map << id << "\t" << current_title << endl;
            continue;
        }

        if (strncmp("  </page>", line.c_str(), 9) == 0) {
            in_text = false;
            continue;
        }

        if (textstart_re.Match(sline, 0, RE2::UNANCHORED, matches, 1)) {
            /* This is the beginning of a text. */
            line = line.substr(matches[0].length() + 
                               ((int)matches[0].data() - (int)line.c_str()));
            if (id)
                in_text = true;
        }

        if (!in_text)
            continue;

        /* Now we look for all links. */
        
        
    }

    return 0;
}


void inline normalize_link(string *link)
{
    for (int i=0; i < link->length(); i++) {
        if ((*link)[i] == ' ') {
            (*link)[i] == '_';
        } 
        else if (i > 0) {
            (*link)[i] = tolower((*link)[i]);
        }
    }
}
