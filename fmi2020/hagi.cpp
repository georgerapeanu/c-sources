#include <cstdio>

using namespace std;

FILE *f = fopen("hagi.in","r");
FILE *g = fopen("hagi.out","w");

const int NMAX = 2e6;
const int MOD = 1e9 + 7;

int k,n,m;

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
    return 1LL * fact[n] * (1LL * ifact[k] * ifact[n - k] % MOD) % MOD;
}

int main() {

    fact[0] = 1;

    for(int i = 1; i <= NMAX; i++) {
        fact[i] = 1LL * fact[i - 1] * i % MOD;
    }

    ifact[NMAX] = lgpow(fact[NMAX],MOD - 2);

    for(int i = NMAX - 1; i >= 0; i--) {
        ifact[i] = 1LL * ifact[i + 1] * (i + 1) % MOD;
    }

    fscanf(f,"%d %d %d",&k,&n,&m);
    fprintf(g,"%d\n",int(1LL * comb(n + k - 1,k - 1) * comb(m + k - 1,k - 1) % MOD));

    fclose(f);
    fclose(g);

    return 0;
}
