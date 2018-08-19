#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <deque>
using namespace std;
FILE *f = fopen("ghiozdan.in","r");
FILE *g = fopen("ghiozdan.out","w");
int N,W;
int fr[205];
int dp[2][75005];
int ant[2][75005];
int D[75005],stq,drq;
int C[75005];
void solve(int st,int dr,int W){
    if(st == dr || !W){
        for(int i = st;i <= W;i += st){
            fprintf(g,"%d\n",st);
        }
        return ;
    }
    int mid = (st + dr) / 2;
    for(int j = 0;j <= W;j++){
            dp[(st & 1) ^ 1][j] = 1 << 28;
    }
    dp[(st & 1) ^ 1][0] = 0;
    for(int i = st,l = (st & 1),nonl = (st & 1) ^ 1;i <= dr;i++,swap(nonl,l)){
        memset(dp[l],0x3f3f3f3f,sizeof(dp[l]));
        if(!fr[i]){
            for(int j = 0;j <= W;j++){
                dp[l][j] = dp[nonl][j];
                ant[l][j] = (i <= mid ? j : ant[nonl][j]);
            }
            continue;
        }
        for(int r = 0;r < i;r++){
            stq = 1;
            drq = 0;
            for(int j = r;j <= W;j += i){
                int cost = dp[nonl][j] - (j / i);
                while(stq <= drq && j - D[stq] > fr[i] * i){
                    stq++;
                }
                while(stq <= drq && C[drq] >= cost){
                    drq--;
                }
                D[++drq] = j;
                C[drq] = cost;
                dp[l][j] = C[stq] + (j / i);
                ant[l][j] = (i <= mid ? j : ant[nonl][D[stq]]);
            }
        }
    }
    int tmp = ant[dr & 1][W];
    solve(st,mid,tmp);
    solve(mid + 1,dr,W - tmp);
}
int main()
{
    fscanf(f,"%d %d",&N,&W);
    for(int i = 1;i <= N;i++){
        int x;
        fscanf(f,"%d",&x);
        fr[x]++;
    }
    for(int j = 1;j <= W;j++){
            dp[0][j] = 1 << 28;
    }
    for(int i = 1,l = 1,nonl = 0;i <= 200;i++,swap(nonl,l)){
        memset(dp[l],0x3f3f3f3f,sizeof(dp[l]));
        if(!fr[i]){
            for(int j = 0;j <= W;j++){
                dp[l][j] = dp[nonl][j];
            }
            continue;
        }
        for(int r = 0;r < i;r++){
            stq = 1;
            drq = 0;
            for(int j = r;j <= W;j += i){
                int cost = dp[nonl][j] - (j / i);
                while(stq <= drq && j - D[stq] > fr[i] * i){
                    stq++;
                }
                while(stq <= drq && C[drq] >= cost){
                    drq--;
                }
                D[++drq] = j;
                C[drq] = cost;
                dp[l][j] = C[stq] + (j / i);
            }
        }
    }
    while(dp[0][W] == 1 << 28){
        W--;
    }
    fprintf(g,"%d %d\n",W,dp[0][W]);
    solve(1,200,W);
    fclose(f);
    fclose(g);
    return 0;
}
