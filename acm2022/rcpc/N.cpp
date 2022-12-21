#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

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

int mult(int a, int b){
  return 1LL * a * b  % MOD;
}

int lgpow(int b, int e){
  int p =1;
  while(e){
    if(e & 1){
      p = mult(p, b);
    }
    b = mult(b, b);
    e >>= 1;
  }
  return p;
}


int main(){

  int w, g, x;
  cin >> w >> g >> x;
  
  vector<int> fact(w + g + 1, 1);
  vector<int> ifact(w + g + 1, 1);

  fact[0] = 1;
  for(int i = 1;i < (int)fact.size();i++){
    fact[i] = mult(fact[i - 1], i);
  }

  ifact[(int)fact.size() - 1] = lgpow(fact[(int)fact.size() - 1], MOD - 2);
  
  for(int i = (int)fact.size() - 2;i >= 0;i--){
    ifact[i] = mult(ifact[i + 1], i + 1);
  }

  auto comb = [&fact, &ifact](int n, int k) {
    return mult(fact[n], mult(ifact[n - k], ifact[k]));
  };
  
  int ans = 0;
  for(int i = 0;i <= g + 1 && w - (x + 1) * i >= 0;i++){
    int term = mult(comb(g + 1, i), comb(w + g - i * (x + 1), g));
    if(i & 1){
      ans = sub(ans, term);
    } else {
      ans = add(ans, term);
    }
  }

  printf("%d\n", ans);

  return 0;
}
