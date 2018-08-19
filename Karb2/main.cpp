#include <cstdio>
#include <vector>
using namespace std;
FILE *f = fopen("karb2.in","r");
FILE *g = fopen("karb2.out","w");
int dp[100005][2];
vector<int> G[100005];
const int MOD = 666013;
bool U[100005];
int N,K;
int adun(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}
int mult(int a,int b){
    return 1LL * a * b % MOD;
}
int lgpow(int b,int e){
    int p = 1;
    while(e){
        if(e & 1){
            p = mult(p,b);
        }
        b = mult(b,b);
        e >>= 1;
    }
    return p;
}
void dfs(int nod,int tata){
    if(U[nod]){
        dp[nod][1] = 0;
        dp[nod][0] = 1;
        for(auto it:G[nod]){
            if (it != tata){
                dfs(it,nod);
                dp[nod][0] = mult(dp[nod][0],adun(dp[it][0],dp[it][1]));
            }
        }
        return;
    }
    if(G[nod].size() == (tata != 0)){
        dp[nod][0] = 0;
        dp[nod][1] = 1;
        return ;
    }
    dp[nod][1] = 1;
    for(auto it:G[nod]){
        if (it != tata){
            dfs(it,nod);
            dp[nod][1] = mult(dp[nod][1],adun(dp[it][0],dp[it][1]));
        }
    }
    dp[nod][0] = 0;
    for(auto it:G[nod]){
        if (it != tata){
            dp[nod][0] = adun(mult(mult(dp[nod][1],lgpow(adun(dp[it][0],dp[it][1]),MOD - 2)),dp[it][0]),dp[nod][0]);
        }
    }
}
int main()
{
    fscanf(f,"%d %d",&N,&K);
    while(K--){
        int x;
        fscanf(f,"%d",&x);
        U[x] = 1;
    }
    for(int i = 1;i < N;i++){
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(1,0);
    fprintf(g,"%d",dp[1][0]);
    fclose(f);
    fclose(g);
    return 0;
}
