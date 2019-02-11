#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <map>

using namespace std;

class InputReader {
  public:
    static const int BUFF_SIZE = 1 << 17;
    int bp;
    char buff[BUFF_SIZE];
    FILE *fin;
    InputReader (const char *file_name) {
      fin = fopen(file_name, "r");
      bp = BUFF_SIZE - 1;
    }
    void close() {
      fclose(fin);
    }
    void next_char() {
      if (++bp == BUFF_SIZE) {
        fread(buff, sizeof(char), BUFF_SIZE, fin);
        bp = 0;
      }
    }
    InputReader& operator >> (int& num) {
      num = 0;
      while (isdigit(buff[bp]) == 0)
        next_char();
      while (isdigit(buff[bp])) {
        num = num * 10 + buff[bp] - '0';
        next_char();
      }
      return *this;
    }
};

const int MAXT = 1e5;
int MAXP2 = 30;

pair < int, int > v[MAXT];
long long dp[MAXT];
int f;

struct TrieNode {
  vector < int > p;
  TrieNode *son[2];
  TrieNode () {
    son[0] = son[1] = NULL;
  }
} *root = new TrieNode();

void add(TrieNode *node, int num, int p2, int id) {
  if (p2 == 0) {
    node->p.push_back(id);
    return;
  }
  int bit = ((num >> p2) & 1);
  if (node->son[bit] == NULL)
    node->son[bit] = new TrieNode();
  add(node->son[bit], num, p2 - 1, id);
  node->p.push_back(id);
}

void to_subtract(TrieNode *node, int num, int p2, int lim, int id) {
  if (lim == 0) {
    int msk = (((1 << v[id].first) - 1) << (f - v[id].first - 1));
    for (auto j : node->p) {
      int mask = (1 << (f - v[j].first - 1)) - 1;
      if ((v[id].first ^ v[j].first) && (v[id].second & msk) == (v[j].second & msk) && (v[id].second & mask) == (v[j].second & mask))
        dp[id] -= dp[j];
    }
    return;
  }
  int bit = ((num >> p2) & 1);
  if (node->son[bit] == NULL)
    return;
  to_subtract(node->son[bit], num, p2 - 1, lim - 1, id);
}

//map < int, long long > mp;

int main()
{
    int t;
    InputReader fin("fft2d.in");
    fin >> f >> t;
    MAXP2 = f;
    for (int i = 0; i < t; ++i)
      fin >> v[i].first >> v[i].second;
    fin.close();
    sort(v, v + t);
    long long ans = (1LL << (2LL * f - 2));
    reverse(v, v + t);
    for (int i = 0; i < t; ++i) {
      dp[i] = (1LL << (f - v[i].first - 1));
      to_subtract(root, v[i].second, MAXP2, v[i].first, i);
      add(root, v[i].second, MAXP2, i);
    }
    for (int i = 0; i < t; ++i)
      ans -= dp[i] * (1LL << v[i].first);
    //cerr << sizeof(mp) * mp.size();
    ofstream fout("fft2d.out");
    fout << ans << '\n';
    fout.close();
    return 0;
}
