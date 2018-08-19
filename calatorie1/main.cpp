#include <iostream>
#include <cstdio>
#define MOD 997
using namespace std;
FILE *f=fopen("calatorie1.in","r");
FILE *g=fopen("calatorie1.out","w");
int N,X;
int K,val;
int dp[50005];
int p[]={1,1,2,5,14,42,132,429,433,874,844,960,636,135,486,17,62,892,925,930,36,678,151,317,833,839};
int main()
{
    fscanf(f,"%d%d%d",&X,&K,&N);
    K/=2;
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        dp[val]=-1;
    }
    /*p[0]=1;
    cout<<"{";
    for(int i=1;i<=K/2;i++)
    {
        for(int j=0;j<i;j++)
        {
            p[i]+=(p[j]*p[i-1-j])%MOD;
            p[i]%=MOD;
        }
        cout<<p[i]<<",";
    }
    */
    dp[0]=1;
    for(int i=1;i<=X;i++)
    {
        if(dp[i]>=0)
        {
            for(int j=max(0,i-K);j<i;j++)
            {
                if(dp[j]==-1)
                    continue;
                dp[i]+=(dp[j]*2*p[i-j-1])%MOD;
                dp[i]%=MOD;
            }
        }
    }
    fprintf(g,"%d",dp[X]);
    return 0;
}
