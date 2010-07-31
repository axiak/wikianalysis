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
RE2 link_re("(?:</text|\\[\\[(.+?)(?:\\||\\]\\]))");

void inline normalize_link(string *link);

int main(int argc, char**argv)
{
    ofstream adj_file("./wp_adjlist.dat", ios::out | ios::trunc),
        id_map("./wp_idmap.dat", ios::out | ios::trunc);
    string line;
    long long id = 0;
    StringPiece *matches = new StringPiece[20];
    StringPiece sline;
    string current_title, current_link;
    bool in_text = false;
    bool redirect = false;
    string title;
    int start = 0;
    size_t tmp;
    int num_processed = 0;

    while (!cin.eof()) {
        getline(cin, line);

        sline.set(line.c_str(), line.length());

        if (strncmp("  <page>", line.c_str(), 8) == 0) {

            if (id) {
                adj_file << endl;
                ++num_processed;
                if (num_processed % 10000 == 0) {
                    cout << "Finished with " << num_processed << endl;
                }
            }
            in_text = false;
            redirect = false;
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
            }
            else {
                continue;
            }
            id_map << id << "\t" << current_title << endl;
            adj_file << current_title;

            getline(cin, line);
            if (strncmp(line.c_str(), "    <redirect", 13) == 0) {
                /* This is a redirect */
                redirect = true;
            }
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
            sline.set(line.c_str(), line.length());
            if (id)
                in_text = true;
        }

        if (!in_text)
            continue;

        start = 0;
        /* Now we look for all links. */
        while (link_re.Match(sline, start, RE2::UNANCHORED, matches, 2)) {
            if (strncmp(matches[0].data(), "</text", 6) == 0) {
                in_text = false;
                break;
            }
            start = matches[0].length() + ((int)matches[0].data() - (int)sline.data());
            current_link = matches[1].as_string();
            tmp = current_link.find_first_of(':');
            if (tmp != -1 && tmp < 8) {
                continue;
            }
            normalize_link(&current_link);
            if (redirect) {
                adj_file << "\tR:" << current_link;
            }
            else {
                adj_file << "\t" << current_link;
            }                
            //cout << current_link << endl;
        }
    }

    return 0;
}


void inline normalize_link(string *link)
{
    for (int i=0; i < link->length(); i++) {
        if ((*link)[i] == ' ') {
            (*link)[i] = '_';
        } 
    }
    (*link)[0] = toupper((*link)[0]);
}
