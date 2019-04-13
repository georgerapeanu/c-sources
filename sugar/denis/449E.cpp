#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 1e6;
const int MOD = 1e9 + 7;

int q;

int f[NMAX + 5];
int phi[NMAX + 5];
int cost[NMAX + 5];

int pre_n[NMAX + 5];
int pre_l[NMAX + 5];
int pre_s[NMAX + 5];

int main() {

    for(int x = 2; x <= NMAX; x++) {
        phi[x] += x - 1;

        phi[x] %= MOD;

        for(int y = 2 * x; y <= NMAX; y += x) {
            phi[y] -= phi[x];
            if(phi[y] < 0) {
                phi[y] += MOD;
            }
        }
    }

    for(int x = 1; x <= NMAX; x++) {
        for(int k = 1; 1LL * k * x <= NMAX; k++) {
            cost[k * x] += 1LL * k * phi[x] % MOD;
            if(cost[k * x] >= MOD) {
                cost[k * x] -= MOD;
            }
        }
        cost[x] += x;
        cost[x] %= MOD;
    }

    for(int L = 1; L <= NMAX; L++) {
        f[L] = (1LL * L * (2 * L - 1) * (L - 1) / 3 - 1LL * L * L) % MOD;
        f[L] += 2 * cost[L];
        f[L] %= MOD;
    }

    for(int L = 1; L <= NMAX; L++) {
        pre_n[L] = (pre_n[L - 1] + f[L]) % MOD;
        pre_l[L] = (pre_l[L - 1] + (1LL * f[L] * L % MOD)) % MOD;
        pre_s[L] = (pre_s[L - 1] + (1LL * (1LL * f[L] * L % MOD) * L % MOD)) % MOD;
    }

    scanf("%d",&q);

    while(q--) {
        int n,m;
        scanf("%d %d",&n,&m);
        if(n > m) {
            swap(n,m);
        }
        int ans = 0;

        ans = ((1LL * n * m + n + m + 1) % MOD) * pre_n[n] % MOD;
        ans = (ans + MOD - ((1LL * (n + 1 + m + 1) % MOD) * pre_l[n] % MOD)) % MOD;
        ans = (ans + pre_s[n]) % MOD;

        printf("%d\n",ans);
    }


    return 0;
}
