#include <cstdio>
#define MOD 666013
using namespace std;
FILE *f=fopen("unuzero.in","r");
FILE *g=fopen("unuzero.out","w");
int dp[2][1000005];
int N,p,q,rez;
int main()
{
    fscanf(f,"%d\n%d %d",&N,&p,&q);
    dp[0][0]=1;
    for(int i=1;i<=N;i++)
    {
        dp[0][i]=dp[0][i-1]-(i>=2 ? dp[0][i-2]:0)+dp[1][i-1]+dp[0][i-1];
        dp[0][i]%=MOD;
        dp[1][i]=(i>=p ? dp[0][i-p]:0)-(i-q-1>=0 ?dp[0][i-q-1]:0);
        dp[1][i]%=MOD;
    }
    fprintf(g,"%d",(dp[0][N]-dp[0][N-1]+dp[1][N]-1+MOD)%MOD);
    fclose(f);
    fclose(g);
    return 0;
}
