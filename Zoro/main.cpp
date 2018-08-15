#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f = fopen("zoro.in","r");
FILE *g = fopen("zoro.out","w");
pair<int,int> pos[1000005];
int dp[1005][1005];
int L[1005];
int C[1005];
int N,M;
int main(){
    fscanf(f,"%d %d",&N,&M);
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= M;j++){
            int val;
            fscanf(f,"%d",&val);
            pos[val] = {i,j};
            dp[i][j] = - (1 << 28);
        }
    }
    for(int i = 1;i <= N;i++){
        L[i] = - (1 << 28);
    }
    for(int i = 1;i <= M;i++){
        C[i] = - (1 << 28);
    }
    for(int i = 1;i <= N * M;i++){
        int x = pos[i].first;
        int y = pos[i].second;
        if(x == N && y == M){
            dp[x][y] = 1;
            L[x] = 1;
            C[y] = 1;
        }
        else{
            dp[x][y] = max(L[x],C[y]) + 1;
            L[x] = dp[x][y];
            C[y] = dp[x][y];
        }
    }
    fprintf(g,"%d",dp[1][1]);
    fclose(f);
    fclose(g);
    return 0;
}
