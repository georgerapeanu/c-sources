#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *f = fopen("frumos.in","r");
FILE *g = fopen("frumos.out","w");
const int OFF = 30;
int dp[2][105][60][30];
int tmp[2][105][30][30];
const int MOD = 666013;
int bonus[30];
int N,K;
void adun(int &a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
}
void scad(int &a,int b){
    a -= b;
    if(a < 0){
        a += MOD;
    }
}
int main(){
    fscanf(f,"%d %d",&N,&K);
    for(int i = 1;i <= 26 + OFF;i++){
        if(i == OFF){
            continue;
        }
        for(int j = 1;j <= 26;j++){
            dp[0][1][i][j] = (j - (i - OFF) <= 26 && j - (i - OFF) > 0);
        }
    }
    for(int i = 2;i <= N;i++){
        memset(dp[1 ^ (i & 1)],0,sizeof(dp[1 ^ (i & 1)]));
        memset(tmp[1 ^ (i & 1)],0,sizeof(tmp[1 ^ (i & 1)]));
        for(int j = 1;j <= i;j++){
            int ceva = 0;
            for(int k = 0;k <= 26;k++){
                for(int l = 0;l <= 26;l++){
                    adun(ceva,tmp[i & 1][j][k][l]);
                    scad(dp[i & 1][j][OFF][l],tmp[i & 1][j][k][l]);
                    scad(dp[i & 1][j][OFF][k],tmp[i & 1][j][k][l]);
                }
            }
            for(int k = 0;k <= 26;k++){
                adun(dp[i & 1][j][OFF][k],ceva);
            }
            for(int k = 1;k <= 26 + OFF;k++){
                if(k == OFF){
                    continue;
                }
                for(int l = 1;l <= 26;l++){
                    if(l + k - OFF > 0 && l + k - OFF <= 26){
                        adun(dp[1 ^ (i & 1)][j][k][l + k - OFF],dp[i & 1][j][k][l]);
                    }
                    if(l + k - OFF <= 26 && l + k - OFF > 0)adun(tmp[1 ^ (i & 1)][j + 1][l + k - OFF][l],dp[i & 1][j][k][l]);
                    else adun(tmp[1 ^ (i & 1)][j + 1][l][0],dp[i & 1][j][k][l]);
                }
            }
            for(int nk = 1;nk <= 26 + OFF;nk++){
                if(nk == OFF){
                    continue;
                }
                for(int nl = 1;nl <= 26;nl++){
                    adun(dp[1 ^ (i & 1)][j][nk][nl],(nl - (nk - OFF) > 0 && nl - (nk - OFF) <= 26) * dp[i & 1][j][OFF][(nl - (nk - OFF))]);
                }
            }
        }
    }
    int rez = 0;
    for(int i = 1;i <= 26 + OFF;i++){
        for(int j = 1;j <= 26;j++){
            adun(rez,dp[N & 1][K][i][j]);
        }
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
