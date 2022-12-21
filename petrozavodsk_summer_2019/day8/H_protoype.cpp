#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;

int add(int a,int b){
  a += b;
  if(a >= MOD){
    a -= MOD;
  }
  return a;
}

int sub(int a, int b){
  a -= b;
  if(a < 0){
    a += MOD;
  }
  return a;
}

int mult(int a, int b){
  return 1LL * a * b % MOD;
}

int lgpow(int b, int e){
  int p = 1;

  while(e){
    if(e & 1){
      p = mult(p, b);
    }
    b = mult(b, b);
    e >>= 1;
  }

  return p;
}

const int NMAX = 60;

int main(){

  vector<vector<int> > dp(NMAX + 1, vector<int>(NMAX + 1, 0));
  vector<int> fact(NMAX + 1, 1);
  vector<int> ifact(NMAX + 1, 1);
  vector<int> inv(NMAX + 1, 1);

  for(int i = 1;i <= NMAX;i++){
    fact[i] = mult(fact[i - 1], i);
  }
  ifact[NMAX] = lgpow(fact[NMAX], MOD - 2);

  for(int i = NMAX - 1;i >= 0;i--){
    ifact[i] = mult(ifact[i + 1], i + 1);
    inv[i + 1] = mult(ifact[i + 1], fact[i]);
  }

  auto comb = [&fact, &ifact](int n, int k) {
    return mult(fact[n], mult(ifact[n - k], ifact[k]));
  };

  for(int i = 2;i <= NMAX;i++){
    dp[0][i] = mult(mult(mult(i, i - 1), fact[i]), inv[4]);
  }

  for(int h = 1;h <= NMAX;h++){
    for(int i = 1;i <= NMAX;i++){
      for(int j = 0;j < i;j++){
        dp[h][i] = add(dp[h][i], mult(add(mult(dp[h - 1][j], fact[i - j - 1]), mult(dp[h - 1][i - j - 1], fact[j])), comb(i - 1, j)));
      }
    }
  }

  int t;
  scanf("%d", &t);

  for(int test = 1;test <= t;test++){
    int n, k;
    scanf("%d %d", &n, &k);
    k--;
    printf("Case #%d: %d\n", test, dp[k][n]);
  }

  return 0;
}
