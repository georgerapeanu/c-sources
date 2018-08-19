#include <cstdio>
using namespace std;
FILE *f=fopen("planeta.in","r");
FILE *g=fopen("planeta.out","w");
long long dp[31];
int N;
long long K;
void solve(int N,long long K,int offset)
{
    for(int i=1;i<=N;i++)
    {
        if(K>dp[i-1]*dp[N-i])K-=dp[i-1]*dp[N-i];
        else
        {
            fprintf(g,"%d ",offset+i);
            long long k=K/dp[N-i];
            if(k*dp[N-i]==K)k--;
            solve(i-1,k+1,offset);
            K-=k*dp[N-i];
            solve(N-i,K,offset+i);
            return ;
        }
    }
}
int main()
{
    dp[0]=1;for(int i=1;i<=30;i++)for(int j=0;j<i;j++)dp[i]+=dp[j]*dp[i-1-j];
    fscanf(f,"%d %lld",&N,&K);
    solve(N,K,0);
    fclose(f);
    fclose(g);
    return 0;
}
