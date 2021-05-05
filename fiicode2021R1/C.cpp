#include <bits/stdc++.h>

using namespace std;

int n;
int m;
int a[5005];
int b[5005];

int inv[5005][5005][2];
long long dp[5005][5005];

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
    }
    
    scanf("%d",&m);

    for(int i = 1;i <= m;i++){
        scanf("%d",&b[i]);
    }

    for(int i = n;i;i--){
        for(int j = m;j;j--){
            inv[i][j][0] = inv[i][j + 1][0] + (a[i] > b[j]);
            inv[i][j][1] = inv[i + 1][j][1] + (b[j] > a[i]);
            dp[i][j] = max(dp[i][j + 1] + inv[i][j][1],dp[i + 1][j] + inv[i][j][0]);
        }
    }

    long long ans = dp[1][1];

    for(int i = 1;i < n;i++){
        for(int j = i + 1;j <= n;j++){
            ans += (a[i] > a[j]);
        }
    }
    
    for(int i = 1;i < m;i++){
        for(int j = i + 1;j <= m;j++){
            ans += (b[i] > b[j]);
        }
    }

    printf("%lld\n",ans);
    return 0;
}
