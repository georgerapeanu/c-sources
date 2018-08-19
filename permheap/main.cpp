#include <cstdio>
#define MOD 666013
using namespace std;
FILE *f=fopen("permheap.in","r");
FILE *g=fopen("permheap.out","w");
long long dp[200005];
int N,dr;
int lg[200005];
bool cresc;
long long x,y;
void inv(long long a,long long b)
{
    if(b==0) ;
    else
    {
        inv(b,a%b);
        int x0,y0;
        x0=y;
        y0=x-y*(a/b);
        x=x0;
        y=y0;
    }
}
int main()
{
    lg[0]=-1;
    for(int i=1;i<=200002;i++) lg[i]=1+lg[i/2];
    fscanf(f,"%d",&N);
    dp[1]=dp[0]=1;
    long long val=1;
    for(int i=2;i<=N;i++)
    {
        if((i&(i^(i-1)))==i)
            cresc=1;
        if(i/(i&(i^(i-1)))==3)
            cresc=0;
        if(cresc)
        {
            dr++;
            x=1;
            y=0;
            inv(dr,MOD);
            x=(MOD+x%MOD)%MOD;
            val=(((val*(i-1))%MOD)*x)%MOD;
        }
        else
        {
            x=1;
            y=0;
            inv(i-dr-1,MOD);
            x=(MOD+x%MOD)%MOD;
            val=(((val*(i-1))%MOD)*x)%MOD;
        }
        dp[i]=(((dp[dr]*dp[i-1-dr])%MOD)*val)%MOD;
    }
    fprintf(g,"%lld",dp[N]);
    return 0;
}
