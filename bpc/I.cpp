#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353; // change to something else
struct ModInt {
  int x;
  ModInt(int x = 0) : x(x + (x < 0) * MOD - (x >= MOD) * MOD){}
  ModInt operator+(ModInt o) { return x + o.x; }
  ModInt operator-(ModInt o) { return x - o.x; }
  ModInt operator*(ModInt o) { return 1LL * x * o.x % MOD; }
  ModInt operator/(ModInt b) { return *this * b.inv(); }
  ModInt inv() { return pow(MOD - 2); }
  ModInt pow(long long e) {
    if (!e) return 1;
    ModInt r = pow(e / 2); r = r * r;
    return e % 2 ? *this * r : r;
  }
  bool operator==(ModInt o) { return x == o.x; }
};

// Good MOD: (119 << 23 + 1), (5 << 25 + 1), (5LL << 55 + 1)
void DFT(vector<ModInt> &a, bool rev) {
  int n = a.size(); auto b = a; 
  assert(!(n & (n - 1)));
  ModInt g = 1; while (g.pow((MOD - 1) / 2) == 1) g = g + 1;
  if (rev) g = g.inv();
  
  for (int step = n / 2; step; step /= 2) {
    ModInt w = g.pow((MOD - 1) / (n / step)), wn = 1; 
    for (int i = 0; i < n / 2; i += step) {
      for (int j = 0; j < step; ++j) {
        auto u = a[2 * i + j], v = wn * a[2 * i + j + step];
        b[i + j] = u + v; b[i + n / 2 + j] = u - v;
      }
      wn = wn * w;
    }
    swap(a, b);
  }
  if (rev) {
    auto n1 = ModInt(n).inv();
    for (auto& x : a) x = x * n1;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int k, m;
  cin >> k >> m;
  vector<ModInt> base_poly(16, ModInt(1));

  for(int i = 1; i <= m; i++) {
    string s;
    cin >> s;
    int index = ('0' <= s[0] && s[0] <= '9' ? s[0] - '0':10 + s[0] - 'A');
    base_poly[index] = ModInt(0);
  }
  
  int max_sum = 15 * k + 1;
  while(max_sum & (max_sum - 1)) {
    max_sum++;
  }

  vector<ModInt> answer(1);
  answer[0] = 1;

  answer.resize(max_sum);
  base_poly.resize(max_sum);
  DFT(answer, false);
  DFT(base_poly, false);

  int e = k;
  while (e > 0) {
    if (e & 1) {
      for (int i = 0; i < max_sum; ++i) {
        answer[i] = answer[i] * base_poly[i];
      }
    }
    e /= 2;
    for (auto &it : base_poly) {
      it = it * it;
    }
  }
//  for(int i = 0; (1 << i) < k; i++ ) {
//    if((k >> i) & 1) {
//      for(int i = 0; i < max_sum; i++) {
//        answer[i] = answer[i] * base_poly[i];
//      }
//    }
//    if((k >> (i + 1))) {
//      for(auto &it: base_poly) {
//        it = it * it;
//      }
//    }
//  }

  DFT(answer, true);

  for(int i = 1; i < answer.size(); i++) {
    answer[i] = answer[i - 1] + answer[i];
  }

  int q;
  cin >> q;

  while(q--) {
    int s1, s2;
    cin >> s1 >> s2;

    s2 = min(s2, (int)answer.size() - 1);
    s1--;
    ModInt q_answer = 0;
    if(s1 <= s2) {
      q_answer = q_answer + answer[s2];
      if(s1 >= 0) {
        q_answer = q_answer - answer[s1];
      }
    }
    cout << q_answer.x << "\n";
  }

  return 0;
}
