#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("countbst.in","r");
FILE *g = fopen("countbst.out","w");

const int NMAX = 6e6;
const int KMAX = 2e5;
const int MOD = 1e9 + 7;

int fact[NMAX + 5];
int ifact[NMAX + 5];

int n,k;
int a[KMAX + 5];


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


int catalan(int n) {
    return (1LL * (1LL * fact[2 * n] * ifact[n] % MOD) * ifact[n + 1] % MOD);
}

///test k = 0;
int main() {

    fact[0] = 1;

    for(int i = 1; i <= NMAX; i++) {
        fact[i] = 1LL * i * fact[i - 1] % MOD;
    }

    ifact[NMAX] = lgpow(fact[NMAX],MOD - 2);
    for(int i = NMAX - 1; i >= 0; i--) {
        ifact[i] = 1LL * (i + 1) * ifact[i + 1] % MOD;
    }

    int t;
    fscanf(f,"%d",&t);

    while(t--) {

        fscanf(f,"%d %d",&n,&k);

        for(int i = 1; i <= k; i++) {
            fscanf(f,"%d",&a[i]);
        }

        if(k == 0) {
            fprintf(g,"%d\n",catalan(n));
            continue;
        }

        int ans = 1;
        int roots = 0;

        int st_val = 1 << 30,dr_val = - (1 << 30);
        int st = 1,dr = k;

        for(int i = 1; i <= k; i++) {
            if(st_val <= a[i] && a[i] <= dr_val) {
                dr = i - 1;
                break;
            }
            st_val = min(st_val,a[i]);
            dr_val = max(dr_val,a[i]);
        }

        st_val = 1 << 30;
        dr_val = - (1 << 30);

        for(int i = k; i >= 1; i--) {
            if(st_val <= a[i] && a[i] <= dr_val) {
                st = i + 1;
                break;
            }

            st_val = min(st_val,a[i]);
            dr_val = max(dr_val,a[i]);
        }

        for(int i = st; i <= dr; i++) {
            if((i == 1 || a[i - 1] <= a[i]) && (i == k || a[i] <= a[i + 1])) {
                roots++;
            }
            else if((i == 1 || a[i - 1] >= a[i]) && (i == k || a[i] >= a[i + 1])) {
                roots++;
            }
        }

        ans = 1LL * ans * roots % MOD;
        sort(a + 1,a + 1 + k);

        ans = 1LL * ans * catalan(n - a[k] + a[1]) % MOD;

        for(int i = 2; i <= k; i++) {
            ans = 1LL * ans * catalan(a[i] - a[i - 1] - 1) % MOD;
        }

        fprintf(g,"%d\n",ans);

    }
    fclose(f);
    fclose(g);

    return 0;
}
