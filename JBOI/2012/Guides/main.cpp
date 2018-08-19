#include <iostream>
#define inf (1<<28)
using namespace std;
int dp[105][1<<15];
int N,M;
int X[105][20];
int S[20];
int main()
{
    cin>>N>>M;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            {cin>>X[i][j];S[j]+=X[i][j];}
    for(int i=0;i<=N;i++)for(int j=0;j<(1<<M);j++)dp[i][j]=inf;
    dp[0][0]=0;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<(1<<M);j++)
        {
            if(dp[i][j]==inf)continue;
            dp[i+1][j]=min(dp[i][j],dp[i+1][j]);
            for(int k=1;k<=M;k++)
            {
                if(!((j>>(k-1))&1))
                {
                    dp[i+1][j+(1<<(k-1))]=min(dp[i+1][j+(1<<(k-1))],dp[i][j]+S[k]-X[i+1][k]);
                }
            }
        }
    }
    cout<<dp[N][(1<<M)-1];
    return 0;
}
