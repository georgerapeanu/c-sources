#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <cstdio>

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

const int MAXN = 2e5;
const int MOD = 1e9 + 7;

vector < int > g[MAXN + 1], stk, sol;
int v[MAXN + 1], sp[MAXN + 1];

inline void push_sol() {
  while (stk.empty() == false) {
    sol.push_back(stk.back());
    stk.pop_back();
  }
}

void dfs(int node, int father) {
  if (sp[node] == 0)
    stk.push_back(node);
  else
    push_sol();
  for (auto it : g[node])
    if (it != father)
      dfs(it, node);
  if (sp[node] == 0 && stk.empty() == false)
    stk.pop_back();
}

int main()
{
    int n;
    InputReader fin("countfefete.in");
    fin >> n;
    for (int i = 0; i < n; ++i)
      fin >> v[i];
    for (int i = 1; i < n; ++i) {
      int x, y;
      fin >> x >> y;
      --x; --y;
      g[x].push_back(y);
      g[y].push_back(x);
    }
    fin.close();
    long long ans = 0LL;
    for (int conf = 1; conf < (1 << n); ++conf) {
      memset(sp, 0, sizeof sp);
      sol.clear(); stk.clear();
      int root;
      for (int b = 0; b < n; ++b)
        if (conf & (1 << b)) {
          sp[b] = 1;
          root = b;
          sol.push_back(b);
        }
      dfs(root, -1);
      int mn = 2e9, xr = 0;
      for (auto it : sol) {
        if (sp[it])
          xr ^= v[it];
        //cerr << v[it] << " ";
        mn = mn > v[it] ? v[it] : mn;
      }
      ans += (xr ^ mn);
      //cerr << (xr ^ mn) << '\n';
    }
    ofstream fout("countfefete.out");
    fout << ans % MOD << '\n';
    fout.close();
    return 0;
}
