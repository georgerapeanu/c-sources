#include <cstdio>

using namespace std;

const int NMAX = 500;
const int MOD = 1e9 + 7;

int dp[NMAX + 5][NMAX + 5];
int e[NMAX + 5][NMAX + 5];

int n;
int a[NMAX + 5];

int add(int a, int b) {
    a += b;
    if(a >= MOD) {
        a -= MOD;
    }
    return a;
}

int mult(int a, int b) {
    return 1LL * a * b % MOD;
}

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
    }

    for(int i = 1; i <= n; i++) {
        dp[i][i] = 1;
        e[i][i] = 1;
    }

    for(int l = 1; l < n; l++) {
        for(int i = 1; i <= n - l; i++) {
            int j = i + l;
            for(int k = i; k < j; k++) {
                if(a[k + 1] > a[i]) {
                    e[i][j] = add(e[i][j],mult(dp[i][k],e[k + 1][j]));
                }
            }
            dp[i][j] = e[i + 1][j];
            e[i][j] = add(e[i][j],dp[i][j]);
        }
    }

    printf("%d\n",dp[1][n]);

    return 0;
}
