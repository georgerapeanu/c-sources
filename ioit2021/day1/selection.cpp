#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e3;

int n;
int m;
int r[NMAX + 5];
long long dp[NMAX + 5][NMAX + 5];
int ans[NMAX + 5][NMAX + 5];

int main(){

    scanf("%d %d",&n,&m);

    for(int i = 1;i <= n;i++){
        scanf("%d",&r[i]);
        r[i]++;
    }

    r[n + 1] = m + 1;
    for(int i = 1;i <= n;i++){
        if(r[i + 1] - r[i - 1] - 1 == 1){
            dp[i][i] = 0; 
        }else{
            dp[i][i] = r[i + 1] - r[i - 1] - 1;
        }
        ans[i][i] = i;
    }

    for(int l = 1;l < n;l++){
        for(int i = 1;i + l <= n;i++){
            int j = i + l;
            dp[i][j] = 1e18;
            for(int k = i;k <= j;k++){
                if(dp[i][k - 1] + dp[k + 1][j] <= dp[i][j]){
                    dp[i][j] = dp[i][k - 1] + dp[k + 1][j];
                    ans[i][j] = k;
                }
            }
            dp[i][j] += r[j + 1] - r[i - 1] - 1;
        }
    }

    printf("%lld\n",dp[1][n]);

    return 0;
}

