#include <cstdio>
#include <algorithm>

using namespace std;

int n,p,q;
int a[2005];
int dp[2005][2005];

bool ok(int w) {
    if(n <= p + q) {
        return true;
    }

    int l1 = 0;
    int l2 = 0;

    for(int i = 1; i <= n; i++) {
        while(l1 < i && a[i] - a[l1 + 1] >= w) {
            l1++;
        }
        while(l1 < i && a[i] - a[l2 + 1] >= 2 * w) {
            l2++;
        }
        for(int j = 0; j <= p; j++) {
            dp[i][j] = dp[l2][j] + 1;
            if(j) {
                dp[i][j] = min(dp[i][j],dp[l1][j - 1]);
            }
        }
    }

    for(int i = 0; i <= p; i++) {
        if(dp[n][i] <= q) {
            return true;
        }
    }

    return false;
}

int main() {

    scanf("%d %d %d",&n,&p,&q);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
    }

    sort(a + 1,a + 1 + n);

    int st = 0;
    int dr = 1e9;

    while(dr - st > 1) {
        int mid = st + (dr - st) / 2;

        if(ok(mid)) {
            dr = mid;
        }

        else {
            st = mid;
        }
    }

    printf("%d\n",dr);

    return 0;
}
