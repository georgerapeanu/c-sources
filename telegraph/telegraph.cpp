#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("telegraf.in","r");///switch for ia
FILE *g = fopen("telegraf.out","w");

const int NMAX = 750;
const long long inf = 1LL << 60;

int n;
int v[NMAX + 5];
long long suff[NMAX + 5];
long long dp[2][NMAX + 1][NMAX + 1];

int main(){

    n = 36;///swtich for ia

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d",&v[i]);
        if(v[i] == 0){
            n--;
            i--;
        }
    }

    if(n == 0){
        fprintf(g,"0\n");
        return 0;
    }

    sort(v + 1,v + 1 + n);
    reverse(v + 1,v + 1 + n);

    for(int i = n;i;i--){
        suff[i] = suff[i + 1] + v[i];
    }

    for(int j = 0;j <= n;j++){
        for(int k = 0;k <= n;k++){
            dp[0][j][k] = inf;
        }
    }

    dp[0][1][1] = suff[1];

    long long ans = inf;

    for(int i = 0,l = 0;i <= n;i++,l ^= 1){
        for(int j = 0;j <= n - i;j++){
            for(int k = 0;k <= n - i - j;k++){
                dp[l ^ 1][j][k] = inf;
            }
        }
        for(int j = 0;j <= n - i;j++){
            for(int k = 0;k <= n - i - j;k++){
                if(dp[l][j][k] == inf){
                    continue;
                }
                if(j > 0){
                    dp[l ^ 1][j - 1][k] = min(dp[l ^ 1][j - 1][k],dp[l][j][k]);
                }
                if(j + k <= n){
                    dp[l][j + k][j] = min(dp[l][j + k][j],dp[l][j][k] + suff[i + 1]);
                }
                if(i == n){
                    ans = min(ans,dp[l][j][k]);
                }
            }
        }
    }

    fprintf(g,"%lld\n",ans);

    return 0;
}
