
#include <cstdio>
#include <cstring>

using namespace std;

FILE *f = fopen("dupadealuri.in","r");
FILE *g = fopen("dupadealuri.out","w");

const int MOD1 = 1e9 + 7;
const int MOD2 = 666013;
const int BASE = 31;
const int NMAX = 1e5;

int pw1[NMAX + 5];
int pw2[NMAX + 5];

struct hsh_t {
    int h1;
    int h2;
    int len;

    hsh_t() {
        h1 = h2 = len = 0;
    }

    hsh_t(char c) {
        h1 = c - 'a' + 1;
        h2 = c - 'a' + 1;
        len = 1;
    }

    hsh_t operator + (const hsh_t &other)const {
        hsh_t ans;
        ans.h1 = (1LL * this->h1 * pw1[other.len] + other.h1) % MOD1;
        ans.h2 = (1LL * this->h2 * pw2[other.len] + other.h2) % MOD2;
        ans.len = this->len + other.len;
        return ans;
    }

    bool operator == (const hsh_t &other)const {
        return this->h1 == other.h1 && this->h2 == other.h2 && this->len == other.len;
    }
};

char c[NMAX + 5];
hsh_t pref_sum[NMAX + 5];
hsh_t suff_sum[NMAX + 5];
hsh_t pref_sum2[NMAX + 5];
hsh_t suff_sum2[NMAX + 5];

int main() {

    pw1[0] = pw2[0] = 1;

    for(int i = 1; i <= NMAX; i++) {
        pw1[i] = 1LL * pw1[i - 1] * BASE % MOD1;
        pw2[i] = 1LL * pw2[i - 1] * BASE % MOD2;
    }

    fgets(c + 1,NMAX + 3,f);
    int n = strlen(c + 1);

    n -= (c[n] == '\n' || c[n] == '\0');
    n -= (c[n] == '\n' || c[n] == '\0');

    for(int i = 1; i <= n; i++) {
        pref_sum[i] = pref_sum[i - 1] + hsh_t(c[i]);
        pref_sum2[i] = hsh_t(c[i]) + pref_sum2[i - 1];
    }

    for(int i = n; i; i--) {
        suff_sum[i] = hsh_t(c[i]) + suff_sum[i + 1];
        suff_sum2[i] = suff_sum2[i + 1] + hsh_t(c[i]);
    }

    int ans = 0;

    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j++) {
            ans += ((pref_sum[i - 1] + suff_sum[j + 1]) == (suff_sum2[j + 1] + pref_sum2[i - 1]));
        }
    }

    fprintf(g,"%d\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
