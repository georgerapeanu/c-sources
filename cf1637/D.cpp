#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e2;
const int VMAX = 1e2;
const int inf = 1e9;

int n;
int a[NMAX + 5];
int b[NMAX + 5];
int dp[NMAX + 5][NMAX * VMAX + 5];
int sum_a_b[NMAX + 5];

int main(){
  
  int t;
  scanf("%d", &t);
  while(t--){
    scanf("%d", &n);

    for(int i = 1;i <= n;i++){
      scanf("%d",&a[i]);
    }
  
    for(int i = 1;i <= n;i++){
      scanf("%d",&b[i]);
    }

    for(int i = 1;i <= n;i++){
      sum_a_b[i] = sum_a_b[i - 1] + a[i] + b[i];
    }

    dp[0][0] = 0;

    for(int i = 0;i < n;i++){
      for(int j = 0;j <= (i + 1) * VMAX;j++){
        dp[i + 1][j] = inf;
      }
      for(int j = 0;j <= i * VMAX;j++){
        dp[i + 1][j + a[i + 1]] = min(dp[i + 1][j + a[i + 1]],
                     dp[i][j] + (n - 1) * a[i + 1] * a[i + 1] + (n - 1) * b[i + 1] * b[i + 1] + 2 * a[i + 1] * j + 2 * b[i + 1] * (sum_a_b[i] - j));
        
        dp[i + 1][j + b[i + 1]] = min(dp[i + 1][j + b[i + 1]],
                     dp[i][j] + (n - 1) * a[i + 1] * a[i + 1] + (n - 1) * b[i + 1] * b[i + 1] + 2 * b[i + 1] * j + 2 * a[i + 1] * (sum_a_b[i] - j));
      }
    }
    int ans = 1e9;
    for(int j = 0;j <= n * VMAX;j++){
      ans = min(ans, dp[n][j]);
    }
    printf("%d\n",ans);
  }
    
    return 0;
}
