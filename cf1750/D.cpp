#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;

int count(int k, int lim) {
  if(k == 1){
    return lim;
  }
  vector<int> facts = {};

  for(int i = 2;1LL * i * i <= k;i++){
    if(k % i == 0){
      facts.push_back(i);
    }
    while(k % i == 0){
      k /= i;
    }
  }
  if(k != 1){
    facts.push_back(k);
  }

  int answer = 0;
  int len = facts.size();

  for(int conf = 0;conf < (1 << len);conf++){
    int term = 1;
    for(int i = 0;i < len;i++){
      if((conf >> i) & 1){
        term *= facts[i];
      }
    }
    answer += (lim / term) * (__builtin_popcount(conf) & 1 ? -1:1);
  }
  return answer;
}

int main(){

  int t;

  scanf("%d", &t);

  while(t--){
    int n, m;
    scanf("%d %d", &n, &m);
    vector<int> v(n + 1);

    for(int i = 1;i <= n;i++){
      scanf("%d", &v[i]);
    }
    
    int answer = 1;

    for(int i = 2;i <= n;i++){
      if(v[i - 1] % v[i] != 0){
        answer = 0;
        break;
      }
      answer = 1LL * answer * count(v[i - 1] / v[i], m / v[i]) % MOD;
    }
    
    printf("%d\n", answer);
  }


  return 0;
}
