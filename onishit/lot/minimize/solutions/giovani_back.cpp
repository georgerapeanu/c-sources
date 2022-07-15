#include "minimize.h"
#include <iostream>
#include <vector>

namespace solver {
  using ll = long long;

  const ll INF = 1e18;

  int n, k;
  ll sol = INF;
  std::vector <bool> del;
  std::vector <int> a;

  void back(int pos = 1, int used = 0) {
    if (sol == 0)
      return;

    if (pos == n + 1 || used == k) {
      bool first = true;
      int last = 0;
      ll sum = 0;
      for (int i = 1; i <= n ; ++i) {
        if (del[i]) continue;

        if (first)
          first = false;
        else
          sum = sum + (a[i] ^ last);

        last = a[i];
      }

      sol = std::min(sol, sum);
      return;
    }

    back(pos + 1, used);
    del[pos] = 1;
    back(pos + 1, used + 1);
    del[pos] = 0;
  }

  void modify(int pos, int val) {
    a[pos] = val;
  }

  long long getter() {
    sol = INF;
    if (del.empty()) del.resize(n + 1);
    std::fill(del.begin(), del.end(), 0);
    back();
    return sol;
  }
};

void initialize(int _n, int _k, std::vector <int> _a) {
  solver::n = _n;
  solver::k = std::min(_k, _n);
  solver::a = std::move(_a);
}

void modify(int pos, int val) {
  solver::modify(pos, val);
}

long long calculate() {
  return solver::getter();
}

