#include <iostream>
#include <set>
#include <stdlib.h>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

#define CREATE_PAIR(a, b) (a > b) ? \
  ((((long long)a) << 32) + ((long long)b)) :	\
  ((((long long)b) << 32) + ((long long)a))

#define SPLIT_PAIR(pair, a, b) do { \
    a = (pair) & 0xFFFFFFFF; b = (pair) >> 32;	\
  } while (0)



int main(int argc, char ** argv)
{
  set<long long>edges;
  set<long long>::iterator it;
  string line;
  char_separator<char> sep("\t");

  long from, to;

  while (!cin.eof()) {
    getline(cin, line);
    tokenizer<char_separator<char> > tokens(line, sep);
    int i = 0;
    string from_string;

    BOOST_FOREACH(string t, tokens) {
      if (!i) {
	i++;
	from = atol(t.c_str());
	continue;
      }
      if (to = atol(t.c_str())) {
	edges.insert(CREATE_PAIR(from, to));
      }
      i ++;
    }
  }


  for (it = edges.begin(); it != edges.end(); it++) {
    SPLIT_PAIR(*it, from, to);
    cout << from << "\t" << to << endl;
    cout << to << "\t" << from << endl;
  }

  return 0;
}
