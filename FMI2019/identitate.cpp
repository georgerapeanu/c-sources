#define JUDGE
#include <cstdio>
#include <algorithm>

using namespace std;

#ifdef JUDGE
FILE *f = fopen("identitate.in","r");
FILE *g = fopen("identitate.out","w");
#else
FILE *f = stdin;
FILE *g = stdout;
#endif

const int SIGMA = 10;
const int NMAX = 200;
const int CFMAX = 6;

int fr[SIGMA + 5];
char c[NMAX + 5];

int delta[SIGMA + 5];

long long ans = 0;

const int zile[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

long long dp[SIGMA + 5][CFMAX + 5];
long long C[SIGMA + 5][SIGMA + 5];

void btr(int pas,int sex,int an,int luna,int zi) {
    if(pas == 1) {
        if(fr[1]) {
            fr[1]--;
            btr(pas + 1,1,an,luna,zi);
            fr[1]++;
        }
        if(fr[2]) {
            fr[2]--;
            btr(pas + 1,2,an,luna,zi);
            fr[2]--;
        }
        return ;
    }

    if(pas == 2) {
        for(int i = 1901; i <= 2000; i++) {
            int val = i % 100;
            if(fr[val / 10] > 0 && fr[val % 10] > 0 + (val / 10 == val % 10)) {
                fr[val / 10]--;
                fr[val % 10]--;
                btr(pas + 1,sex,i,luna,zi);
                fr[val % 10]++;
                fr[val / 10]++;
            }
        }
        return ;
    }

    if(pas == 3) {
        for(int i = 1; i <= 12; i++) {
            if(i < 10) {
                if(fr[0] > 0 && fr[i] > 0 + (i == 0)) {
                    fr[0]--;
                    fr[i]--;
                    btr(pas + 1,sex,an,i,zi);
                    fr[0]++;
                    fr[i]++;
                }
            }
            else {
                if(fr[1] > 0 && fr[i - 10] > 0 + (i - 10 == 1)) {
                    fr[1]--;
                    fr[i - 10]--;
                    btr(pas + 1,sex,an,i,zi);
                    fr[1]++;
                    fr[i - 10]++;
                }
            }
        }
        return;
    }

    if(pas == 4) {
        int mx_zi = zile[luna] + (luna == 2 && an % 4 == 0);
        for(int i = 1; i <= mx_zi; i++) {
            if(fr[i % 10] > 0 && fr[i / 10] > 0 + (i / 10 == i % 10)) {
                fr[i % 10]--;
                fr[i / 10]--;
                btr(pas + 1,sex,an,luna,i);
                fr[i % 10]++;
                fr[i / 10]++;
            }
        }
        return ;
    }

    for(int j = 0; j <= fr[0]; j++) {
        dp[0][j] = 1;
    }

    for(int j = fr[0] + 1; j <= CFMAX; j++) {
        dp[0][j] = 0;
    }

    for(int i = 1; i <= SIGMA; i++) {
        for(int j = 0; j <= CFMAX; j++) {
            dp[i][j] = 0;
            for(int k = max(0, j - fr[i]); k <= j; k++) {
                dp[i][j] += dp[i - 1][k] * C[j][k];
            }
        }
    }

    ans += dp[SIGMA][CFMAX];
}

int main() {

    for(int i = 0; i <= SIGMA; i++) {
        C[i][0] = 1;
        for(int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }

    fgets(c + 1,NMAX + 2,f);

    for(int i = 1; c[i] != '\n' && c[i] != '\0'; i++) {
        fr[c[i] - '0']++;
    }

    btr(1,0,0,0,0);

    fprintf(g,"%lld",ans);

    return 0;
}
