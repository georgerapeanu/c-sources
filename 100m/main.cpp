#include <cstdio>
#define MOD 666013
using namespace std;
FILE *f=fopen("100m.in","r");
FILE *g=fopen("100m.out","w");
int dp[2][5005];
int N,K;
int S[5005];
int main()
{
    fscanf(f,"%d",&N);
    dp[0][0]=1;
    for(int i=1;i<=N;i++)
    {
        dp[i%2][0]=0;
        for(int j=1;j<=i;j++)
        {dp[i%2][j]=(1LL*(dp[1-i%2][j]+dp[1-i%2][j-1])*j)%MOD;S[i]=(S[i]+dp[i%2][j])%MOD;}
    }
    fprintf(g,"%d",S[N]);
    fclose(f);
    fclose(g);
    return 0;
}
