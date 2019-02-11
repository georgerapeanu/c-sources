#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MOD = 1e9 + 7;
int s, init_n;

int solve(vector < int > v) {
  vector < int > pos;
  int n = (int) v.size();
  if (n == 1) {
    return v[0];
  }
  for (int i = 1; i < n; ++i)
    if ((v[i] - v[i - 1] + s) % s != 1)
      pos.push_back(i);
  for (int i = 1; i < (int) pos.size(); ++i)
    if (pos[i] - pos[i - 1] != s)
      return -1;
  if (pos.size() == 0)
    return (v.back() + 1) % s;
  int bg = -1;
  if (pos[0] != s - 1)
    bg = (v[pos[0] - 1] + 1) % s;
  int en = -1;
  if (pos.back() != n - 1)
    en = pos.back();
  vector < int > w;
  if (bg != -1)
    w.push_back(bg);
  for (auto it : pos)
    w.push_back(v[it]);
  if (en != -1)
    w.push_back(en);
  if (w.size() == v.size())
    return -1;
  int ans = solve(w);
  if (ans == -1)
    return -1;
  ans = (1LL * ans * s + (bg == -1) ? 0 : pos[0]);
  return ans;
}

int main()
{
    int t;
    ifstream fin("pscfft.in");
    fin >> t;
    ofstream fout("pscfft.out");
    for (int test = 0; test < t; ++test) {
      int n;
      fin >> n >> s;
      vector < int > v(n);
      for (int i = 0; i < n; ++i)
        fin >> v[i];
      fout << solve(v) << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}
