#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;
const int MOD = 1e9 + 7;

int n;
int l[NMAX + 5];
int r[NMAX + 5];
int suff_sum[NMAX + 5];

int lgpow(int b,int e) {
    int p = 1;
    while(e) {
        if(e & 1) {
            p = 1LL * p * b % MOD;
        }
        b = 1LL * b * b %MOD;
        e >>= 1;
    }
    return p;
}

int p_same(int x,int y) {
    int ans = 1;

    int ll = 0,rr = 1e9 + 1;

    for(int i = x; i <= y; i++) {
        ll = max(ll,l[i]);
        rr = min(rr,r[i]);
        ans = 1LL * ans * (r[i] - l[i] + 1) % MOD;
    }

    ans = 1LL * max(0,rr - ll + 1) * lgpow(ans,MOD - 2) % MOD;

    return ans;
}

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&l[i]);
    }

    for(int i = 1; i <= n; i++) {
        scanf("%d",&r[i]);
    }

    int ans = 1;

    for(int i = 1; i < n; i++) {
        int p = (MOD + 1 - p_same(i,i + 1)) % MOD;
        ans = (ans + 3LL * p) % MOD;
    }

    for(int i = n - 1; i; i--) {
        suff_sum[i] = (suff_sum[i + 1] + p_same(i,i + 1)) % MOD;
    }

    for(int i = 1; i < n - 1; i++) {
        ///j = i + 1

        ans = ((ans + 2LL * (MOD + 1LL - p_same(i,i + 1) - p_same(i + 1,i + 2) + p_same(i,i + 2))) % MOD + MOD) % MOD;

        ///j > i + 1
        if(i + 2 < n) {
            ans = (ans + 2LL * (p_same(i,i + 1) - 1) * (suff_sum[i + 2] - (n - i - 2)) % MOD + MOD) % MOD;
        }
    }

    printf("%d\n",ans);

    return 0;
}
