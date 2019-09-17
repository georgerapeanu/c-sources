#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 300;
const int SMAX = NMAX * NMAX;

int n,m,k;
int a[NMAX + 5];
int b[NMAX + 5];
int dp[2][SMAX + 5];
int sum;

int update(int x,int y,int val) {
    if(y < 0 || y > SMAX || dp[x][y] == -1) {
        return -1;
    }
    return dp[x][y] + val;
}

int main() {

    scanf("%d %d %d",&n,&m,&k);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
        sum += a[i];
        if(a[i] < k) {
            printf("Impossible");
            return 0;
        }
    }

    for(int i = 1; i <= m; i++) {
        scanf("%d",&b[i]);
    }

    for(int i = 0; i < 2; i++) {
        for(int j = 0; j <= SMAX; j++) {
            dp[i][j] = -1;
        }
    }

    dp[0][0] = 0;

    for(int i = 1,l = 1; i <= m; i++,l ^= 1) {
        for(int j = 0; j <= SMAX; j++) {
            dp[l][j] = dp[l ^ 1][j];
            dp[l][j] = max(dp[l][j],update(l ^ 1,j - b[i],min(n,b[i])));
        }
    }

    for(int i = sum; i <= SMAX; i++) {
        if(dp[m & 1][i] >= k * n) {
            printf("%d\n",i - sum);
            return 0;
        }
    }
    printf("Impossible");

    return 0;
}
