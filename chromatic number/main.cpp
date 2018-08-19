#include <algorithm>
#include <cstdio>
#define MOD 1000000007
using namespace std;
long long dist[305][305];
long long nrmod[305][305];
int N;
int M,K;
long long dp[305][305];
long long dp2[305][305];
int main() {
    scanf("%d %d %d",&N,&M,&K);
    for(int i=1;i<=N;i++){for(int j=1;j<=N;j++)if(i!=j){dist[i][j]=1LL<<60;nrmod[i][j]=1;}nrmod[i][i]=1;}
    for(int i=1;i<=M;i++)
    {
        int x,y,z;
        scanf("%d %d %d",&x,&y,&z);
        dist[x][y]=dist[y][x]=z;
    }
    for(int k=1;k<=N;k++)
    {
        for(int i=1;i<=N;i++)
        {
            if(i!=k)
            {
                for(int j=1;j<=N;j++)
                {
                    if(j!=i&&j!=k)
                    {
                        if(dist[i][j]>dist[i][k]+dist[k][j])
                        {
                            dist[i][j]=dist[i][k]+dist[k][j];
                            nrmod[i][j]=1LL*nrmod[i][k]*nrmod[k][j];
                        }
                        else if(dist[i][j]==dist[i][k]+dist[k][j])
                        {
                            nrmod[i][j]=nrmod[i][j]+1LL*nrmod[i][k]*nrmod[k][j];
                        }
                    }
                }
            }
        }
    }
    for(int i=1;i<=N;i++)
    {
        dp[1][i]=nrmod[1][i];
        dp2[1][i]=1;
    }
    for(int k=2;k<=K;k++)
    {
        for(int i=1;i<=N;i++)
        {
            dp[k][i]=0;
            for(int j=1;j<=N;j++)
            {
                if(i!=j&&dist[1][j]+dist[i][j]==dist[1][i])
                {
                    if(dp[k][i]<1LL*dp[k-1][j]*nrmod[j][i])
                    {
                        dp[k][i]=1LL*dp[k-1][j]*nrmod[j][i];
                        dp2[k][i]=dp2[k-1][j];
                    }
                    else if(dp[k][i]==1LL*dp[k-1][j]*nrmod[j][i])
                    {
                        dp2[k][i]+=dp2[k-1][j];
                        if(dp2[k][i]>=MOD)dp2[k][i]-=MOD;
                    }
                }
            }
        }
    }
    long long rez=0,rez2=0;
    for(int i=1;i<=N;i++)
    {
        if(dist[1][i]+dist[i][N]>dist[1][N])continue;
        if(rez<dp[K][i]*nrmod[i][N])
        {
            rez=dp[K][i]*nrmod[i][N];
            rez2=dp2[K][i];
        }
        else if(rez==dp[K][i]*nrmod[i][N])
        {
            rez2+=dp2[K][i];
            if(rez2>=MOD)rez2-=MOD;
        }
    }
    printf("%lld %lld",rez,rez2);
    return 0;
}
