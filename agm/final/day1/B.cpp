#include <bits/stdc++.h>
#ifdef LOCAL_DEFINE
#include <dbg.h>
#else
#define dbg(...)
#endif

using namespace std;

int64_t GCD(int64_t a, int64_t b) {
  if (b == 0) return a;
  return GCD(b, a % b);
}

void Solve(int64_t a, int64_t b, vector<int64_t> &ans) {
  int64_t g = GCD(a, b);
  dbg(a, b, g);
  a /= g; b /= g;
  if (b < 0) a = -a, b = -b;

  assert(b > 0);

  if (b == 1) {
    ans.emplace_back(a);
    return;
  }

  ans.emplace_back(a / b);
  Solve(b,a % b,ans);

}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  dbg((-7) / 3, (-7) % 3);

  int q; cin >> q;
  while (q--) {
    int64_t a, b; cin >> a >> b;
    vector<int64_t> ans;
    Solve(a, b, ans);
    cout << ans.size() << ' ';
    for (int x : ans) cout << x << ' ';
    cout << '\n';
  }

  return 0;
}
