#include "minimize.h"
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

namespace solver {
  using ll = long long;

  const ll INF = 1e18;
  const int NMAX = 1e5;
  const int KMAX = 20;

  using std::vector;
  using std::pair;
  using std::priority_queue;

  int n, k;
  ll sum;
  ll sol = INF;
  vector <int> a;
  vector <pair <int, int>> mod;
  vector <vector <ll>> last; 
  priority_queue <pair <ll, int>> s[KMAX + 1];

  void init(int _n, int _k, std::vector <int> &_a) {
    n = _n;
    k = _k;
    a = std::move(_a);
    last.resize(k + 2);

    for (int i = 0; i <= k + 1 ; ++i)
      last[i].resize(n + 2);
    
    sum = 0;
    for (int r = 1; r <= n + 1 ; ++r) {
      if (r > 1 && r <= n)
        sum += a[r] ^ a[r - 1];

      ll cost = 0;
      if (r > 1 && r <= n)
        cost = a[r] ^ a[r - 1];

      for (int l = r - 1; l >= r - k && l >= 1 ; --l) {
        if (l - 1 > 0)
          cost = cost + (a[l] ^ a[l - 1]); 

        if (l - 1 > 0 && r <= n)
          cost = cost - (a[r] ^ a[l - 1]);

        if (cost > 0)
          s[r - l].push({cost, r});

        last[r - l][r] = cost;

        if (l - 1 > 0 && r <= n)
          cost = cost + (a[r] ^ a[l - 1]);
      }
    }
  }

  void push() {
    for (auto it : mod) {
      int i = it.first;
      int val = it.second;

      if (i > 1)
        sum = sum - (a[i] ^ a[i - 1]) + (val ^ a[i - 1]);
      if (i < n)
        sum = sum - (a[i] ^ a[i + 1]) + (val ^ a[i + 1]);

      a[i] = val;
    }

    sort(mod.begin(), mod.end());
    for (int ind = 0, bef = 0; ind < (int)mod.size() ; ++ind) {
      int i = mod[ind].first;

      int nxt = n + 2;
      if (ind + 1 < (int)mod.size())
        nxt = mod[ind + 1].first;

      if (i == nxt)
        continue;

      for (int r = std::max(i, bef + 1); r <= std::min(i + k + 1, n + 1) ; ++r) {
        if (r == nxt)
          break;
        bef = r;

        bool ch = false;

        ll cost = 0;
        if (r > 1 && r <= n) 
          cost = a[r] ^ a[r - 1];

        if (r == i || r - 1 == i)
          ch = true;

        for (int l = r - 1; l >= r - k && l >= 1 ; --l) {
          if (l - 1 > 0)
            cost = cost + (a[l] ^ a[l - 1]); 

          if (l - 1 > 0 && r <= n)
            cost = cost - (a[r] ^ a[l - 1]);

          if (!ch && l - 1 == i)
            ch = true;

          if (ch && cost != last[r - l][r]) {
            last[r - l][r] = cost;

            if (cost > 0)
              s[r - l].push({cost, r});
          }

          if (l - 1 > 0 && r <= n)
            cost = cost + (a[r] ^ a[l - 1]);
        }
      }
    }

    mod.clear();
  }

  struct segment {
    int l, r;
    ll cost;

    bool operator < (const segment &rhs) const {
      if (rhs.r != r)
        return r < rhs.r;

      return l < rhs.l;
    }
  };

  struct state {
    int i;
    vector <long long> val;
  };

  ll solve() {
    vector <segment> v;
    for (int i = 1; i <= k ; ++i) {
      int nr = 1 + (i + 2) * (k - i);

      vector <pair <ll, int>> add;
      while (nr-- && !s[i].empty()) {
        auto it = s[i].top();
        s[i].pop();
        while (!s[i].empty() && s[i].top() == it)
          s[i].pop();

        int r = it.second, l = it.second - i;
        if (last[i][r] != it.first) {
          ++nr;
          continue;
        }

        v.push_back({l - 1, r, it.first}); 
        add.push_back(it);
      }

      for (auto it : add)
        s[i].push(it);
    }

    vector <state> dp;

    dp.emplace_back();
    dp.back().i = 0;
    dp.back().val.resize(k + 1);
    std::fill(dp.back().val.begin(), dp.back().val.end(), 0);

    sort(v.begin(), v.end());
    for (auto seg : v) {
      if (dp.back().i != seg.r) {
        auto aux = dp.back().val;
        dp.emplace_back();
        dp.back().i = seg.r;
        dp.back().val = std::move(aux);
      }

      int last = dp.size() - 2;
      // at most k iterations
      while (last >= 1 && dp[last].i > seg.l)
        --last;

      auto &now = dp.back();
      auto &prev = dp[last];
      for (int j = 0; j <= k - (seg.r - seg.l - 1) ; ++j) {
        now.val[j + seg.r - seg.l - 1] = std::max(now.val[j + seg.r - seg.l - 1], prev.val[j] + seg.cost);
        if (j + seg.r - seg.l - 2 >= 0)
        now.val[j + seg.r - seg.l - 1] = std::max(now.val[j + seg.r - seg.l - 1], now.val[j + seg.r - seg.l - 2]); 
      }
    }

    ll ans = 0;

    for (int j = 0; j <= k ; ++j)
      ans = std::max(ans, dp.back().val[j]);

    return sum - ans;
  }

  void modify(int pos, int val) {
    mod.push_back({pos, val});
  }

  ll getter() {
    if (mod.empty() && sol != INF)
      return sol;

    if (!mod.empty())
      push();

    sol = solve();

    return sol;
  }
};
int qi;
int qm;

void initialize(int _n, int _k, std::vector <int> _a) {
  qm = qi = 0;
  assert(_k <= _n);
  assert(_a.size() == _n + 1);
  assert(1 <= _n && _n <= 100000);
  assert(1 <= _k && _k <= 2);
  for(int i = 0;(int)i < _a.size();i++){
    assert(0 <= _a[i] && _a[i] < (1LL << 31) - 1);
  }
  solver::init(_n, _k, _a);
}

void modify(int pos, int val) {
  qm++;
  assert(qm <= 50000);
  solver::modify(pos, val);
}

long long calculate() {
  qi++;
  assert(qi <= 1000);
  return solver::getter();
}

