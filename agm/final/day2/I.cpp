#include <bits/stdc++.h>

using namespace std;


uint64_t lgpow(uint64_t b, uint64_t e, uint64_t mod) {
  uint64_t ans = 1;
  b %= mod;
  while (e) {
    if (e & 1){
      ans = (__uint128_t)ans * b % mod;
    }    
    b = (__uint128_t)b * b % mod;
    e >>= 1;
  }
  return ans;
}

bool check_composite(uint64_t n, uint64_t a, uint64_t d, int s) {
  uint64_t x = lgpow(a, d, n);
  if (x == 1 || x == n - 1){
    return false;
  }
  for (int r = 1; r < s; r++) {
    x = (__uint128_t)x * x % n;
    if (x == n - 1){
      return false;
    }
  }
  return true;
};

bool is_prime(uint64_t n) { 
  if (n < 2){
    return false;
  }

  int r = 0;
  uint64_t d = n - 1;
  while ((d & 1) == 0) {
    d >>= 1;
    r++;
  }

  for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (n == a){
      return true;
    }
    if (check_composite(n, a, d, r)){
      return false;
    }
  }
  return true;
}

const int NMAX = 1e6 + 1;
int n,q;
long long s;
int stuff[NMAX + 5];

int main(){
  
  scanf("%d %lld %d",&n,&s,&q);

  int len = 0;
  for(int i = 1;i <= n;i += 2){
    stuff[++len] = is_prime(s);
    s += 4 * i + 2;
  }

  for(int i = 1;i <= len;i++){
    stuff[i] += stuff[i - 1];
  }


  while(q--){
    int a,b;
    scanf("%d %d",&a,&b);
    a = (a >> 1) + 1;
    b = (b >> 1) + 1;
    printf("%d\n",stuff[b] - stuff[a - 1]);
  }

  return 0;
}
