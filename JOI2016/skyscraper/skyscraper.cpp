#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MOD = 1e9 + 7;
const int NMAX = 1e2;
const int LMAX = 1e3;

int n,l;
int v[NMAX + 5];
int dp[2][NMAX + 5][LMAX + 5][3];

void add_to(int a,int j,int k,int e,int val) {
///    printf("to %d %d %d %d %d\n",a,j,k,e,val);
    if(a < 0 || a > 1)return ;
    if(j < 0 || j > n)return ;
    if(k < 0 || k > l)return ;
    if(e < 0 || e > 2)return ;
    dp[a][j][k][e] += val;
    dp[a][j][k][e] %= MOD;
}

int main() {

    scanf("%d %d",&n,&l);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&v[i]);
    }

    sort(v + 1,v + 1 + n);

    dp[1][0][0][0] = 1;
    dp[1][0][0][1] = 2;
    dp[1][0][0][2] = 1;

    for(int i = 1,a = 1; i < n; i++,a ^= 1) {
        memset(dp[1 ^ a],0,sizeof(dp[1 ^ a]));
//        if(i == 2)printf("%d\n",dp[a][0][2][1]);
        for(int j = 0; j <= n; j++) {
            for(int k = 0; k <= l; k++) {
                for(int e = 0; e < 3; e++) {
                    if(dp[a][j][k][e] == 0) {
                        continue;
                    }
                    int cost = (v[i + 1] - v[i]) * (2 * j + e);
///                    printf("from %d %d %d %d\n",a,j,k,e);
                    add_to(a ^ 1,j + 1,k + cost,e,1LL * dp[a][j][k][e] * j % MOD);
                    add_to(a ^ 1,j,k + cost,e,2LL * dp[a][j][k][e] * j % MOD);
                    add_to(a ^ 1,j - 1,k + cost,e,1LL * dp[a][j][k][e] * j % MOD);

                    add_to(a ^ 1,j + 1,k + cost,e,1LL * dp[a][j][k][e] * e % MOD);
                    add_to(a ^ 1,j,k + cost,e,1LL * dp[a][j][k][e] * e % MOD);
                    add_to(a ^ 1,j + 1,k + cost,e - 1,1LL * dp[a][j][k][e] * e % MOD);
                    add_to(a ^ 1,j,k + cost,e - 1,1LL * dp[a][j][k][e] * e % MOD);
                }
            }
        }
    }

    int ans = 0;

    for(int k = 0; k <= l; k++) {
        ans += dp[n & 1][0][k][0];
        ans %= MOD;
    }

    printf("%d\n",ans);

    return 0;
}
