#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 1e6;

int n;
char s[2 * NMAX + 5];

int sa[NMAX + 5];
int pos[2 * NMAX + 5];

int pref_sum[NMAX + 5];

int pref_min[NMAX + 5];
int suff_min[NMAX + 5];

int tmp[2 * NMAX + 5];

int gap;

bool cmp(int a,int b) {
    if(pos[a] != pos[b]) {
        return pos[a] < pos[b];
    }

    a += gap;
    b += gap;

    return pos[a] < pos[b];
}

void build_sa() {
    sort(sa + 1,sa + 1 + n,[&](int a,int b) {
        return s[a] < s[b];
    });
    for(int i = 1; i <= n; i++) {
        pos[sa[i]] = pos[sa[i - 1]] + (s[sa[i - 1]] != s[sa[i]]);
        pos[sa[i] + n] = pos[sa[i]];
    }

    for(gap = 1; gap <= n; gap *= 2) {
        sort(sa + 1,sa + 1 + n,cmp);
        tmp[sa[1]] = 1;
        for(int i = 2; i <= n; i++) {
            tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1],sa[i]);
            tmp[sa[i] + n] = tmp[sa[i]];
        }

        for(int i = 1; i <= 2 * n; i++) {
            pos[i] = tmp[i];
        }
    }
}

int main() {

    fgets(s + 1,NMAX + 5,stdin);

    n = strlen(s + 1);
    n -= (s[n] == '\n');

    for(int i = n + 1; i <= 2 * n; i++) {
        s[i] = s[i - n];
    }

    for(int i = 1; i <= n; i++) {
        sa[i] = i;
    }

    for(int i = 1; i <= n; i++) {
        pref_sum[i] = (s[i] == '(' ? 1 : -1) + pref_sum[i - 1];
        pref_min[i] = pref_sum[i];

        if(i > 1) {
            pref_min[i] = min(pref_min[i - 1],pref_min[i]);
        }
    }

    for(int i = n; i; i--) {
        suff_min[i] = pref_sum[i];

        if(i < n) {
            suff_min[i] = min(suff_min[i + 1],suff_min[i]);
        }
    }

    build_sa();

    int cnt = pref_sum[n];

    if(cnt > 0) {
        for(int i = 1; i <= n; i++) {
            if(suff_min[sa[i]] - pref_sum[sa[i] - 1] >= 0 && (pref_sum[n] - pref_sum[sa[i] - 1]) + pref_min[sa[i] - 1] >= 0) {
                for(int j = sa[i]; j <= n; j++) {
                    fprintf(stdout,"%c",s[j]);
                }
                for(int j = 1; j < sa[i]; j++) {
                    fprintf(stdout,"%c",s[j]);
                }
                for(int j = 1; j <= cnt; j++) {
                    fprintf(stdout,")");
                }

                return 0;
            }
        }
    }
    else {
        for(int i = 1; i <= n; i++) {
            if(suff_min[sa[i]] - pref_sum[sa[i] - 1] >= cnt && (pref_sum[n] - pref_sum[sa[i] - 1]) + pref_min[sa[i] - 1] >= cnt) {
                for(int j = 1; j <= -cnt; j++) {
                    fprintf(stdout,"(");
                }
                for(int j = sa[i]; j <= n; j++) {
                    fprintf(stdout,"%c",s[j]);
                }
                for(int j = 1; j < sa[i]; j++) {
                    fprintf(stdout,"%c",s[j]);
                }

                return 0;
            }
        }
    }

    return 0;
}
