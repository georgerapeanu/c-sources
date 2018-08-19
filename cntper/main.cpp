#include <cstdio>
#define MOD 666013
#define rmod(x) (x%MOD+MOD)%MOD
using namespace std;
FILE *f=fopen("cntper.in","r");
FILE *g=fopen("cntper.out","w");
int N,T;
int dp[1000005];
int main()
{
    dp[0]=1;
    for(int i=1;i<=1000000;i++) dp[i]=(dp[i-1]*26)%MOD;
    for(int i=1;i<=1000000;i++)
    {
        for(int j=2*i;j<=1000000;j+=i)
            dp[j]=rmod(dp[j]-dp[i]);
    }
    fscanf(f,"%d",&T);
    while(T)
    {
        fscanf(f,"%d",&N);
        fprintf(g,"%d\n",dp[N]);
        T--;
    }
    return 0;
}
