#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e2;

int n,m;

int cntRight[NMAX + 5];

int perm[NMAX + 5];

long long dp[NMAX + 5];

int main(){

  scanf("%d %d",&n,&m);

  for(int i = 1;i <= m;i++){
    int x,y;
    scanf("%d %d",&x,&y);
    if(x > y){
      swap(x,y);
    }
    cntRight[x]++;
  }

  for(int i = n;i;i--){
    for(int j = 1;j <= n;j++){
      if(perm[j] == 0 && cntRight[j] == (n - j)){
        perm[j] = i;
        for(int k = j;k >= 0;k--){
          if(perm[k] == 0){
            cntRight[k]++;
          }
        }
        break;
      }
    }
  }

  int _max = -1e9;
  for(int i = n;i >= 1;i--){
    _max = max(_max,perm[i]);
    if(perm[i] == _max){
      dp[i] = 1;
    }
    int _min = 1e9;
    for(int j = i + 1;j <= n;j++){
      if(perm[i] < perm[j]){
        _min = min(_min,perm[j]);
      }
      if(perm[j] == _min){
        dp[i] += dp[j];
      }
    }
  }

  int _min = 1e9;
  long long ans = 0;
  for(int i = 1;i <= n;i++){
    _min = min(_min,perm[i]);
    if(_min == perm[i]){
      ans += dp[i];
    }
  }

  printf("%lld\n",ans);

  return 0;
}
