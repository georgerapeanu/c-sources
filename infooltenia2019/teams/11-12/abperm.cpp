#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("abperm.in","r");
FILE *g = fopen("abperm.out","w");

const int NMAX = 1e5;
const int MOD = 1e9 + 7;

int t,n;

int a[NMAX + 5];
int b[NMAX + 5];

int fact[NMAX + 5];
int ifact[NMAX + 5];

int fr[NMAX + 5];

int inva[NMAX + 5];
int invb[NMAX + 5];

int same[NMAX + 5];

bool was_ok[NMAX + 5];

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
    if(k < 0 || k > n) {
        return 0;
    }

    return 1LL * (1LL * fact[n] * ifact[k] % MOD) * ifact[n - k] % MOD;
}

int main() {

    fact[0] = 1;

    for(int i = 1; i <= NMAX; i++) {
        fact[i] = 1LL * i * fact[i - 1] % MOD;
    }

    ifact[NMAX] = lgpow(fact[NMAX],MOD - 2);

    for(int i = NMAX - 1; i >= 0; i--) {
        ifact[i] = 1LL * ifact[i + 1] * (i + 1) % MOD;
    }

    fscanf(f,"%d %d",&t,&n);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&a[i]);
    }

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&b[i]);
    }

    int ans = 0;

    for(int i = 1; i <= n; i++) {
        fr[i] = 1;
    }

    int cnt = 0;

    for(int i = 0; i <= n; i++) {
        if(cnt == 0) {
            ans = (ans + comb(n,i)) % MOD;
            was_ok[i] = true;
        }

        if(i != n) {
            fr[b[n - i]]--;
            if(fr[b[n - i]] == 0) {
                cnt++;
            }
            fr[a[i + 1]]++;
            if(fr[a[i + 1]] == 1) {
                cnt--;
            }
        }
    }

    if(t == 2) {
        for(int i = 1; i <= n; i++) {
            inva[a[i]] = i;
            invb[b[i]] = i;
        }

        for(int i = n; i; i--) {
            same[a[i]] = 1;
            if(i < n && invb[a[i]] < n && a[i + 1] == b[invb[a[i]] + 1]) {
                same[a[i]] = same[a[i + 1]] + 1;
            }
        }

        for(int i = 1; i <= n; i++) {
            if(was_ok[inva[i] - 1] && same[i] >= n - (inva[i] - 1) - (invb[i] - 1)) {
                ans -= comb(inva[i] + invb[i] - 2,inva[i] - 1);
                if(ans < 0) {
                    ans += MOD;
                }
            }
        }
    }

    fprintf(g,"%d",ans);

    fclose(f);
    fclose(g);

    return 0;
}
