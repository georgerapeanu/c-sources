#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
FILE *f = fopen("leduri.in","r");
FILE *g = fopen("leduri.out","w");
int N;
int V[100005];
int dp[100005][8];
int main()
{
    fscanf(f,"%d",&N);
    for(int i = 1;i <= N;i++){
        int a;
        fscanf(f,"%d",&a);
        V[i] ^= a;
    }
    for(int i = 1;i <= N;i++){
        int a;
        fscanf(f,"%d",&a);
        V[i] ^= a;
    }
    for(int i = 0;i <= N;i++){
        for(int j = 0;j < 8;j++){
            dp[i][j] = 1 << 28;
        }
    }
    dp[0][0] = 0;
    for(int i = 1;i <= N;i++){
        for(int j = 0;j < 8;j++){
            if((((j & 1) != 0) + ((j & 2) != 0) + ((j & 4) != 0)) % 2 == V[i - 1] || i == 1){
                dp[i][j] = min(min(dp[i - 1][(j >> 1) + 4],dp[i - 1][(j >> 1)]) + (j & 1),1 << 28);
            }
        }
    }
    int rez = 1 << 28;
    for(int j = 0;j < 8;j++){
        if(V[N] == (((j & 1) != 0) + ((j & 2) != 0)) % 2){
            rez = min(rez,dp[N][j]);
        }
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
