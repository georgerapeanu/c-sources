#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

FILE *f = fopen("bbreeds.in","r");
FILE *g = fopen("bbreeds.out","w");

const int NMAX = 1e3;

int n;
int dp[NMAX + 5][NMAX + 5];
char c[NMAX + 5];
int pref_sum[NMAX + 5];

int main() {

    fgets(c + 1,NMAX + 5,f);
    n = strlen(c + 1);
    n -= (c[n] == '\n');

    for(int i = 1; i <= n; i++) {
        pref_sum[i] = pref_sum[i - 1] + (c[i] == '(' ? 1:-1);
    }

    dp[0][0] = 1;

    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            int k = pref_sum[i] - j;

            if(k < 0) {
                continue;
            }

            int nj = j - (c[i] == '(' ? 1:-1);
            int nk = k - (c[i] == '(' ? 1:-1);

            if(nj >= 0) {
                dp[i][j] += dp[i - 1][nj];
            }
            if(nk >= 0) {
                dp[i][j] += dp[i - 1][j];
            }

            dp[i][j] %= 2012;
        }
    }

    int k = pref_sum[n];
    if(k == 0) {
        fprintf(g,"%d\n",dp[n][0]);
    }
    else {
        fprintf(g,"0\n");
    }

    fclose(f);
    fclose(g);

    return 0;
}
