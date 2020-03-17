#include <cstdio>

using namespace std;

const int NMAX = 1e5;
const int MOD = 1e9 + 7;

int n;
int k;

int fact[NMAX + 5];
int ifact[NMAX + 5];

int lgpow(int b,int e) {
    int p = 1;

    while(e) {
        if(e & 1) {
            p = 1LL * p * b % MOD;
        }
        b = 1LL * b * b % MOD;
        e >>= 1;
    }
    return p;
}

int comb(int n,int k) {
    return (1LL * (1LL * fact[n] * ifact[k] % MOD) * ifact[n - k] % MOD);
}

int main() {

    fact[0] = 1;

    for(int i = 1; i <= NMAX + 2; i++) {
        fact[i] = 1LL * i * fact[i - 1] % MOD;
    }

    ifact[NMAX + 2] = lgpow(fact[NMAX + 2],MOD - 2);

    for(int i = NMAX + 1; i >= 0; i--) {
        ifact[i] = 1LL * ifact[i + 1] * (i + 1) % MOD;
    }

    scanf("%d %d",&n,&k);

    int ans = 0;

    for(int i = 0; i < k; i++) {
        ans += 1LL * (i & 1 ? -1 : 1) * comb(n + 1,i) * lgpow(k - i,n) % MOD;
        if(ans < 0) {
            ans += MOD;
        }
        else if (ans >= MOD) {
            ans -= MOD;
        }
    }

    printf("%d\n",ans);

    return 0;
}

