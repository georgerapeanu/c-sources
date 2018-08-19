#include <cstdio>
#include <algorithm>
#define INF 10000000000000000LL
using namespace std;
FILE *f=fopen("podm.in","r");
FILE *g=fopen("podm.out","w");
int N,i,j,k;
long long V[505];
long long dp[505][505];
int main()
{
    fscanf(f,"%d",&N);
    for(i=0;i<=N;i++)
    {
        fscanf(f,"%lld",&V[i]);
    }
    for(i=1;i<N;i++)
        dp[i][i+1]=V[i-1]*V[i]*V[i+1];
    for(i=N;i>=1;i--)
    {
        for(j=i+2;j<=N;j++)
        {
            dp[i][j]=INF;
            for(k=i;k<j;k++)
                dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]+V[i-1]*V[k]*V[j]);
        }
    }
    fprintf(g,"%lld",dp[1][N]);
    fclose(f);
    fclose(g);
    return 0;
}
