#include <bits/stdc++.h>

using namespace std;

int n;
int a[5005];
int b[5005];
long long dp[5005][5005];
long long pref[5005];
long long suff[5005];
int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
    }

    for(int i = 1;i <= n;i++){
        scanf("%d",&b[i]);
    }

    for(int i = 1;i <= n;i++){
        pref[i] = 1LL * a[i] * b[i] + pref[i - 1];
    }

    for(int i = n;i;i--){
        suff[i] = 1LL * a[i] * b[i] + suff[i + 1];
    }

    long long ans = pref[n];

    for(int i = n;i;i--){
        for(int j = i;j <= n;j++){
            dp[i][j] = dp[i + 1][j - 1] + 1LL * a[i] * b[j] + (i != j) * 1LL * a[j] * b[i];
            ans = max(ans,dp[i][j] + pref[i - 1] + suff[j + 1]);
        }
    }

    printf("%lld\n",ans);

    return 0;
}
