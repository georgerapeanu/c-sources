#include <bits/stdc++.h>

using namespace std;

const int NMAX = 5e5;

int t;
int n,k;

int r[NMAX + 5];
int p[NMAX + 5];
int dp[2];
int ndp[2];

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d %d",&n,&k);

        for(int i = 0;i < k;i++){
            scanf("%d",&r[i]);
        }

        for(int i = 1;i <= n;i++){
            scanf("%d",&p[i]);
        }

        p[0] = -1e8;

        dp[0] = dp[1] = 0;

        for(int i = 1;i <= n;i++){
            ndp[0] = ndp[1] = n + 1;
            for(int j = 0;j < k;j++){
                if(dp[j] == n + 1){
                    continue;
                }
                if(p[i] - p[i - 1] >= r[j]){
                    ndp[j] = min(ndp[j],dp[j]);
                }
                if(p[i] - p[dp[j]] >= r[1 - j]){
                    ndp[1 - j] = min(ndp[1 - j],i - 1);
                }
            }
            dp[0] = ndp[0];
            dp[1] = ndp[1];
        }

        bool ok = (dp[0] < n + 1 || dp[1] < n + 1);

        printf("%d\n",ok);
    }

    return 0;
}

