#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

FILE *f = fopen("munte.in","r");
FILE *g = fopen("munte.out","w");

int N,K,D;
long long dp[102][52][52];
int V[52];

long long solve(int N,int D,int K){
    if(N == 0){
        if(D > 1){
            return 0;
        }
        return 1;
    }
    memset(dp,0,sizeof(dp));
    dp[0][0][((V[1] == 0 && K) ? 1 : 0)] = 1;
    for(int i = 1;i <= D;i++){
        for(int j = 1;j <= N;j++){
            for(int k = 0;k <= K;k++){
                if(k && j == V[k]){
                    dp[i][j][k] += dp[i - 1][j - 1][k - 1] + dp[i - 1][j][k - 1] + dp[i - 1][j + 1][k - 1];
                }
                if(k == K || j !=  V[k + 1]){
                    dp[i][j][k] += dp[i - 1][j - 1][k] + dp[i - 1][j][k] + dp[i - 1][j + 1][k];
                }
            }
        }
        if(i == D){
            for(int k = 0;k <= K;k++){
                if(k && 0 == V[k]){
                    dp[D][0][k] += dp[D - 1][0][k - 1] + dp[D - 1][1][k - 1];
                }
                if(k == K || 0 != V[k + 1]){
                    dp[D][0][k] += dp[D - 1][0][k] + dp[D - 1][1][k];
                }
            }
        }
    }
    return dp[D][0][K];
}

int main(){

    fscanf(f,"%d %d %d",&N,&D,&K);

    for(int i = 1;i <= K;i++){
        fscanf(f,"%d",&V[i]);
        if(V[i] == 0 && V[i] != 1 && V[i] != K){
            fprintf(g,"0");
            return 0;
        }
    }

    fprintf(g,"%lld",solve(N,D,K) - solve(N - 1,D,K));

    fclose(f);
    fclose(g);

    return 0;
}
