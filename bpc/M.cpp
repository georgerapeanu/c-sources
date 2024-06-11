#include <bits/stdc++.h>
#ifndef LOCAL_DEFINE
#define dbg(...)
#else
#include "dbg.h"
#endif

using namespace std;


/**
 * Author: Lucian Bicsi
 * Date: 2021-01-01
 * License: CC0
 * Source: folklore
 * Description: Operators for modular arithmetic. You need 
 * to set {\tt MOD} to some number first and then you can use 
 * the structure.
 */

const int MOD = (int)1e9 + 7;

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
  bool operator==(const ModInt o) const { return x == o.x; }
};


ModInt BASE1 = 37;
ModInt BASE2 = 43; 

vector<ModInt> pw1;
vector<ModInt> pw2;
vector<ModInt> invpw1;
vector<ModInt> invpw2;

struct Hash {
  ModInt a;
  ModInt b;

  Hash() {
    a = b = 0;
  }
  Hash(int value) {
    a = value;
    b = value;
  }
  bool operator==(const Hash&other) const {
    return a == other.a && b == other.b;
  }

  void Add(int n, Hash x) {
    a = a * pw1[n] + x.a;
    b = b * pw2[n] + x.b;
  }
  
  void AddMy(int n, Hash x) {
    a = a + x.a * pw1[n];
    b = b + x.b * pw2[n];
  }
  
  void Sub(int n, int value) {
    a = a - ModInt(value) * pw1[n];
    b = b - ModInt(value) * pw2[n];
  }

  void Shr(int n) {
    a = a * invpw1[n];
    b = b * invpw2[n];
  }
};

void prepare_pw(int n) {
  pw1.push_back(1);
  pw2.push_back(1);
  invpw1.push_back(1);
  invpw2.push_back(1);

  ModInt invBASE1 = BASE1.inv();
  ModInt invBASE2 = BASE2.inv();

  for(int i = 1; i <= n; i++) {
    pw1.push_back(pw1.back() * BASE1);
    pw2.push_back(pw2.back() * BASE2);
    invpw1.push_back(invpw1.back() * invBASE1);
    invpw2.push_back(invpw2.back() * invBASE2);
  }
}


void DFS(int node, const vector<vector<int>> &g, vector<int> &lin) {
  for (int x : g[node]) {
    lin.push_back(0);
    DFS(x, g, lin);
    lin.push_back(1);
  }
}

void SolveTest() {
  int n; cin >> n;
  vector<vector<int>> g(n);
  for (int i = 1; i < n; ++i) {
    int p; cin >> p; --p;
    g[p].emplace_back(i);
  }

  if(n == 1) {
    cout << 1 << "\n";
    return;
  }

  vector<Hash> lft(n), rgt(n);
  vector<int> sz(n);
  vector<bool> is_sym(n);

  vector<int> lin;
  DFS(0, g, lin);

  int lin_sz = lin.size();

  for(int i = 0; i < lin_sz; i++){
    lin.push_back(lin[i]);
  }
  for(int i = 0; i < lin_sz; i++){
    lin.push_back(lin[i]);
  }
  vector<int> inv_lin;
  for(int i = 0; i < lin.size(); i++) {
    inv_lin.push_back(1 - lin[i]);
  }

  Hash a(0);
  Hash b(0);

  for(int i = lin_sz - 1; i >= 0; i--) {
    a.Add(1, Hash(inv_lin[i]));
  }

  for(int i = lin_sz; i < 2 * lin_sz; i++) {
    b.Add(1, Hash(lin[i]));
  }

  int count = 0;
  for (int i = lin_sz; i < 2 * lin_sz; i++) {
    count += (a == b);
    //test split between 
    b.Sub(lin_sz - 1, lin[i]);
    b.Add(1, Hash(lin[i + lin_sz]));
    count += (a == b);
    //test split on this 
    a.Sub(0, inv_lin[i - lin_sz]);
    a.Shr(1);
    a.AddMy(lin_sz - 1, inv_lin[i]);
    
    /*
    bool ok = true;

    for(int j = 0; j < lin_sz; j++) {
      ok &= (inv_lin[i - 1 - j] == lin[i + j]);
    }
    count += ok;
    ok = true;
    for(int j = 0; j < lin_sz; j++) {
      ok &= (inv_lin[i - 1 - j] == lin[i + 1 + j]);
    }
    count += ok;
    */
  }
  cout << count / 2 << "\n";
}


int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  const int N = (int)3e6 + 10;
  prepare_pw(N);

  int t; cin >> t;
  while (t--) {
    SolveTest();
  }
}
