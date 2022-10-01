#include <bits/stdc++.h>

using namespace std;

const int NMAX = 60;
const int MOD = 998244353;
// win(n) = has(n) + loss(n - 2)

int add(int a, int b){
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

int mult(int a, int b) {
  return 1LL * a * b % MOD;
}

int lgpow(int b, int e){
  int p = 1;

  while(e){
    if(e & 1){
      p = mult(p, b);
    }
    e >>= 1;
    b = mult(b, b);
  }
  return p;
}

int comb(int n, int k){
  int ans = 1;

  for(int i = k + 1;i <= n;i++){
    ans = mult(ans, i);
    ans = mult(ans, lgpow(i - k, MOD - 2));
  }

  return ans;
}

int main(){

  int t;

  scanf("%d", &t);

  vector<int> win(NMAX + 1, 0);
  vector<int> loss(NMAX + 1, 0);

  win[2] = 1;
  loss[2] = 0;

  for(int i = 4;i <= NMAX;i += 2){
    win[i] = add(comb(i - 1, i / 2), loss[i - 2]);
    loss[i] = sub(sub(comb(i, i / 2), win[i]), 1);
  }

  while(t--){
    int n;
    scanf("%d", &n);
    printf("%d %d %d\n", win[n], loss[n], 1);
  }


    return 0;
}
