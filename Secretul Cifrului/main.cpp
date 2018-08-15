#include <cstdio>
#include <vector>
#define MOD 19997
using namespace std;
FILE *f=fopen("cifru.in","r");
FILE *g=fopen("cifru.out","w");
int N,K;
vector<int> D;
int dp[2005];
int fa[2005];
int invfa[2005];
int lgpow(int b,int e)
{
    int p=1;
    while(e)
    {
        if(e&1)p=(1LL*p*b)%MOD;
        b=(1LL*b*b)%MOD;
        e>>=1;
    }
    return p;
}
int A(int N,int K)
{
    return 1LL*fa[N]*invfa[N-K]%MOD;
}
int main()
{
    fscanf(f,"%d %d",&N,&K);
    for(int i=2;i<=N;i++)
    {
        if(K%i==0)
        {
            D.push_back(i);
        }
    }
    dp[0]=1;
    fa[0]=1;
    for(int i=1;i<=2000;i++)fa[i]=(1LL*i*fa[i-1])%MOD;invfa[2000]=lgpow(fa[2000],MOD-2);
    for(int i=2000-1;i>=0;i--)invfa[i]=(1LL*(i+1)*invfa[i+1])%MOD;
    for(int i=1;i<=N;i++)
    {
        dp[i]=dp[i-1];
        for(auto it:D)
        {
            if(it>i)continue;
            dp[i]=(dp[i]+1LL*dp[i-it]*A(i-1,it-1))%MOD;
        }
    }
    fprintf(g,"%d",dp[N]);
    fclose(f);
    fclose(g);
    return 0;
}
