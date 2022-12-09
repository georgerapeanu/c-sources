#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int lgpow(int b, int e){
  int p = 1;

  while(e){
    if(e & 1){
      p = 1LL * p * b % MOD;
    }
    b = 1LL * b * b % MOD;
    e >>= 1;
  }
  return p;
}

int main(){
  
  int fact = 1;

  int n;
  scanf("%d", &n);
  int answer = 1;

  for(int i = 1;i <= 2 * n;i++){
    fact = 1LL * i * fact % MOD;
    if(i == n) answer = 1LL * answer * lgpow(fact, MOD - 2) % MOD;
    else if(i == n + 1) answer = 1LL * answer * lgpow(fact, MOD - 2) % MOD;
    else if(i == 2 * n) answer = 1LL * answer * fact % MOD;
  }

  printf("%d\n", answer);

  return 0;
}
