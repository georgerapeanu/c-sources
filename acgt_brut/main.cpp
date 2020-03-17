#include <cstdio>

using namespace std;

FILE *f = fopen("acgt.in","r");
FILE *g = fopen("acgt.ok","w");

int dp[2][4];

const int MOD = 666013;

int main(){

    int n;
    fscanf(f,"%d",&n);

    dp[1][0] = 1;
    dp[1][1] = 1;
    dp[1][2] = 1;
    dp[1][3] = 1;

    for(int i = 1;i < n;i++){
        int l = i & 1;
        int nl = l ^ 1;
        dp[nl][0] = 0;
        dp[nl][1] = 0;
        dp[nl][2] = 0;
        dp[nl][3] = 0;

        dp[nl][0] = (dp[nl][0] + dp[l][0]) % MOD;
        dp[nl][1] = (dp[nl][1] + dp[l][0]) % MOD;
        dp[nl][2] = (dp[nl][2] + dp[l][0]) % MOD;
        dp[nl][3] = (dp[nl][3] + dp[l][0]) % MOD;

        dp[nl][0] = (dp[nl][0] + dp[l][1]) % MOD;
        dp[nl][2] = (dp[nl][2] + dp[l][1]) % MOD;
        dp[nl][3] = (dp[nl][3] + dp[l][1]) % MOD;

        dp[nl][0] = (dp[nl][0] + dp[l][2]) % MOD;
        dp[nl][1] = (dp[nl][1] + dp[l][2]) % MOD;

        dp[nl][3] = (dp[nl][3] + dp[l][3]) % MOD;
    }

    fprintf(g,"%d\n",(dp[n & 1][0] + dp[n & 1][1] + dp[n & 1][2] + dp[n & 1][3]) % MOD);

    fclose(f);
    fclose(g);

    return 0;
}
