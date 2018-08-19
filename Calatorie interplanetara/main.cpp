#include <cstdio>
#include <algorithm>
#define inf 625e10
using namespace std;
FILE *f=fopen("calatorie.in","r");
FILE *g=fopen("calatorie.out","w");
long long T,N,sumh,rez;
long long dp[55][551];
long long H[55],n[55];
int main()
{
    fscanf(f,"%lld",&T);
    while(T)
    {
        sumh=0;
        rez=inf;
        fscanf(f,"%lld",&N);
        for(long long i=1;i<N;i++)
            fscanf(f,"%lld %lld",&n[i],&H[i]);
        for(long long i=0;i<=N;i++)
            for(long long j=0;j<=550;j++)
                dp[i][j]=inf;
        dp[0][0]=0;
        for(long long i=1;i<=N;i++)
        {
            for(long long j=0;j<=550;j++)
            {
                dp[i][j]=dp[i-1][j]+n[i-1];
                if(j>=H[i-1])
                    dp[i][j]=min(dp[i][j],dp[i-1][j-H[i-1]]);
            }
        }
        for(long long i=0;i<=550;i++)
            if(rez>dp[N][i]+i*i*i*i)
                rez=dp[N][i]+i*i*i*i;
        fprintf(g,"Consumul minim = %lld.\n",rez);
        T--;
    }
    return 0;
}
