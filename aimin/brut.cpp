#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("aimin.in","r");
FILE *g = fopen("aimin.ok","w");

const int NMAX = 1e3;

int n;
int dp[NMAX + 5][NMAX + 5];

int main(){

    fscanf(f,"%d",&n);

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d",&dp[i][i]);
    }

    for(int l = 1;l < n;l++){
        for(int i = 1;i <= n - l;i++){
            int j = i + l;
            dp[i][j] = 1 << 30;
            for(int k = i;k < j;k++){
                dp[i][j] = min(dp[i][j],1 + max(dp[i][k],dp[k + 1][j]));
            }
        }
    }

    fprintf(g,"%d\n",dp[1][n]);

    fclose(f);
    fclose(g);
    
    return 0;
}
