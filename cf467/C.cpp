#include <bits/stdc++.h>

using namespace std;

const int NMAX = 5e3;
const long long inf = (1LL << 60);

int n,m,k;
long long dp[2][NMAX + 5];
long long p[NMAX + 5];

int main(){

  scanf("%d %d %d",&n,&m,&k);

  for(int i = 1;i <= n;i++){
    scanf("%lld",&p[i]);
    p[i] += p[i - 1];
  }

  for(int h = 1,l = 1;h <= k;h++,l ^= 1){
    for(int i = 0;i < h * m;i++){
      dp[l][i] = -inf;
    }

    for(int i = h * m;i <= n;i++){
      dp[l][i] = max(dp[l][i - 1],dp[l ^ 1][i - m] + p[i] - p[i - m]);
    }
  }

  printf("%lld\n",dp[k & 1][n]);

  return 0;
}
