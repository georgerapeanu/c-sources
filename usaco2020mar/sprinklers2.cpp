#include <cstdio>

using namespace std;

FILE *f = fopen("sprinklers2.in","r");
FILE *g = fopen("sprinklers2.out","w");

const int MOD = 1e9 + 7;
const int inv2 = (MOD + 1) / 2;
const int inv4 = 1LL * inv2 * inv2 % MOD;

int n;
char c[2005][2005];
int dp[2005][2005];
int ok[2005][2005];
int sp[2005][2005];
int main() {

    fscanf(f,"%d\n",&n);
    for(int i = 1; i <= n; i++) {
        fgets(c[i] + 1,2005,f);
        for(int j = 1; j <= n; j++) {
            ok[i][j] = ok[i - 1][j] + ok[i][j - 1] - ok[i - 1][j - 1] + (c[i][j] == '.');
        }
    }

    sp[0][0] = 1;
    for(int i = 0; i <= n; i++) {
        int sum = 0;
        for(int j = 0; j <= n; j++) {
            sp[i][j] = ((i > 0 ? sp[i - 1][j]:0) + sp[i][j]) % MOD;
            dp[i][j] = sp[i][j];
            if(c[i + 1][j] != 'W') {
                sp[i + 1][j] = (sp[i + 1][j] + (1LL * (1LL * sum * inv2 % MOD) * (i > 0 ? inv2:1) % MOD)) % MOD;
            }
            sum = (sum + dp[i][j] * (c[i][j + 1] != 'W')) % MOD;
        }
    }

    int ans = 0;
    int p2 = 1;

    for(int i = 1; i <= ok[n][n]; i++) {
        p2 = (p2 * 2) % MOD;
    }


    for(int j = 0; j <= n; j++) {
        int tmp = 1LL * dp[n][j] * (c[n][j + 1] == 'W' ? 0:(c[n][j + 1] == '.' ? inv2:1)) % MOD;
        dp[n][j] = tmp;
        tmp = 1LL * tmp * p2 % MOD;
        ans = (ans + tmp) % MOD;
    }

    fprintf(g,"%d\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
