#include <bits/stdc++.h>

using namespace std;

int t;
int n,m;

int ord[2005];
int ma[2005];
int a[20][2005];
int dp[20][1 << 12];
int best[1 << 12];

bool cmp(int a,int b) {
    return ma[a] > ma[b];
}

int main() {

    scanf("%d",&t);

    while(t--) {
        scanf("%d %d",&n,&m);

        for(int j = 1; j <= m; j++) {
            ord[j] = j;
            ma[j] = 0;
        }

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                scanf("%d",&a[i][j]);
                ma[j] = max(ma[j],a[i][j]);
            }
        }

        sort(ord + 1,ord + 1 + m,cmp);

        int ans = 0;
        for(int l = 1; l <= n && l <= m; l++) {
            int j = ord[l];
            for(int conf = 0; conf < (1 << n); conf++) {
                best[conf] = 0;
            }
            for(int conf = 0; conf < (1 << n); conf++) {
                int sum = 0;
                for(int i = 0; i < n; i++) {
                    sum += (a[i + 1][j] * ((conf >> i) & 1));
                }
                int tmp_conf = conf;
                for(int i = 0; i < n; i++) {
                    best[tmp_conf] = max(best[tmp_conf],sum);
                    tmp_conf = ((tmp_conf & 1) << (n - 1)) + (tmp_conf >> 1);
                }
            }

            for(int conf = 0; conf < (1 << n); conf++) {
                dp[l][conf] = best[conf];
                for(int conf2 = conf; conf2; conf2 = (conf2 - 1) & conf) {
                    dp[l][conf] = max(dp[l][conf],dp[l - 1][conf2] + best[conf ^ conf2]);
                }
                ans = max(ans,dp[l][conf]);
            }
        }

        printf("%d\n",ans);

    }

    return 0;
}
