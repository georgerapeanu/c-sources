#include "cetatuie.h"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int INF = 1e9;

struct plateau {
  int len, cnt;
};

ll solve(int n, ll k, int v[]) {
  vector <vector <pair <int, int>>> p(n + 1, vector <pair <int, int>> ());
  vector <int> l(n), r(n);

  ll ans = 0;
  for (int i = 1; i < n ; ++i)
    ans = ans + abs(v[i] - v[i - 1]);

  for (int i = 0; i < n ; ++i) {
    int j = i;
    while (j < n && v[j] == v[i]) 
      ++j; 
    --j;

    l[i] = l[j] = i;
    r[i] = r[j] = j;
    if ((i - 1 < 0 || v[i - 1] > v[i]) && (j + 1 >= n || v[j + 1] > v[i]))
      p[j - i + 1].push_back({i, j});

    i = j;
  }

  auto merge = [&](int st, int dr, int x, int y) {
    r[st] = r[dr] = y;
    l[y] = l[x] = st;
    v[st] = v[y] = max(v[st], v[y]);
    if ((st - 1 < 0 || v[st - 1] > v[st]) && (y + 1 >= n || v[y + 1] > v[st]))
      p[y - st + 1].push_back({st, y});
  };

  vector <plateau> p1, p2;
  for (int len = 1; len < n ; ++len) {
    for (auto it : p[len]) {
      int st = it.first, dr = it.second;
      int val = max(v[st], v[dr]);

      int mn;
      if (st == 0 || dr == n - 1) {
        if (st == 0) {
          mn = v[dr + 1];
          merge(st, dr, dr + 1, r[dr + 1]);
        }
        else {
          mn = v[st - 1];
          merge(l[st - 1], st - 1, st, dr);
        }
        p1.push_back({dr - st + 1, mn - val});
      } else {
        mn = min(v[st - 1], v[dr + 1]);
        if (mn == v[st - 1])
          merge(l[st - 1], st - 1, st, dr);
        if (mn == v[dr + 1]) {
          merge(l[st], r[st], dr + 1, r[dr + 1]);
        }
        p2.push_back({dr - st + 1, mn - val});
      }
    }
  }

  p1.push_back({INF, 0});
  p1.push_back({INF, 0});
  p2.push_back({INF, 0});

  reverse(p1.begin(), p1.end());
  reverse(p2.begin(), p2.end());

  auto inc_plateau = [&](vector <plateau> &p, int l, int tip) {
    int sc = 0;
    if (tip == 1 && p.back().cnt > 1)
      sc = 1;

    int nr = min(1LL * p.back().cnt - sc, k / l);

    ans = ans - 1LL * nr * tip;
    k = k - 1LL * nr * l;

    p.back().cnt -= nr;
    if (p.back().cnt == 0)
      p.pop_back();
  };

  while (k > 0) {
    int l1 = p1.back().len;
    int l2 = p2.back().len;

    if (min({l2, l1}) > k || min({l2, l1}) >= INF)
      break;

    if (l1 * 2 >= l2) {
      inc_plateau(p2, l2, 2);
    } else {
      inc_plateau(p1, l1, 1);
    }
  }

  while (k >= p1.back().len && p1.back().len != INF)
    inc_plateau(p1, p1.back().len, 1);

  return ans;
}

