#include <cstdio>
#include <algorithm>

using namespace std;

int n;
int v[2005];
int dp[2005];

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&v[i]);
    }

    sort(v + 1,v + 1 + n);

    int ans = 0;

    for(int i = n; i; i--) {
        dp[i] = 1;
        for(int j = i + 1; j <= n; j++) {
            if(v[j] % v[i] == 0) {
                dp[i] = max(dp[i],dp[j] + 1);
            }
        }
        ans = max(ans,dp[i]);
    }

    printf("%d\n",ans);

    return 0;
}
