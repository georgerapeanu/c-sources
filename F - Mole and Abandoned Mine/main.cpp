#include <cstdio>
#include <algorithm>
using namespace std;
int N,M;
int C[16][16];
int dp[1<<15][16];
int F[1<<15][16];
int wut(int a,int b)
{
    int rez=0;
    for(int i=1;i<=N;i++)if((b>>(i-1))&1)rez+=F[a][i];
    return rez;
}
int main()
{
    scanf("%d %d",&N,&M);
    for(int i=1;i<=M;i++){int x,y,z;scanf("%d %d %d",&x,&y,&z);C[x][y]=C[y][x]=z;}
    for(int conf=0;conf<(1<<N);conf++)
    {
        for(int j=1;j<=N;j++)
        {
            dp[conf][j]=1<<30;
            for(int k=1;k<=N;k++)
                if((conf>>(k-1))&1)F[conf][j]+=C[k][j];
        }
    }
    dp[1][1]=0;
    for(int conf=1;conf<(1<<N);conf++)
    {
        for(int i=1;i<=N;i++)
        {
            if((conf>>(i-1))&1)
            {
                for(int j=1;j<=N;j++)
                    if(C[i][j]&&((conf>>(j-1))&1)==0)
                        dp[conf|(1<<(j-1))][j]=min(dp[conf|(1<<(j-1))][j],dp[conf][i]+F[conf^(1<<(i-1))][j]);
                int u=(1<<N)-1-conf;
                for(int p=u;p;p=(p-1)&u)
                    dp[conf|p][i]=min(dp[conf|p][i],dp[conf][i]+wut(conf^(1<<(i-1)),p));
            }
        }
    }
    printf("%d",dp[(1<<N)-1][N]);
    return 0;
}
