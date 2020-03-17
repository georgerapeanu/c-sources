#include <cstdio>

using namespace std;

FILE *f = fopen("poligoane.in","r");
FILE *g = fopen("poligoane.out","w");

const int TMAX = 10;
const int NMAX = 2000;

int dp[NMAX + 5];
int t;
int n,mod;

int main(){

    fscanf(f,"%d",&t);

    while(t--){
        fscanf(f,"%d %d",&n,&mod);
        dp[0] = (mod == 1 ? 0 : 1);
        for(int i = 1;i <= n;i++){
            dp[i] = 0;
        }

        for(int j = 3;j <= n;j++){
            for(int i = j;i <= n;i++){
                dp[i] += dp[i - j];
                if(dp[i] >= mod){
                    dp[i] -= mod;
                }
            }
        }

        fprintf(g,"%d\n",dp[n]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
