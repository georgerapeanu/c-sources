#include <cstdio>
#define MOD 30103
using namespace std;
FILE *f=fopen("borg.in","r");
FILE *g=fopen("borg.out","w");
int fact[8001];
int ifact[8001];
int N,M,H,K;
int rez;
int dp[21][21][21];
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
int C(int N,int K)
{
    if(K>N)return 0;
    return (1LL*fact[N]*ifact[K]*ifact[N-K])%MOD;
}
void sol1()
{
    ifact[0]=fact[0]=1;
    for(int i=1;i<=8000;i++)fact[i]=(1LL*fact[i-1]*i)%MOD;
    ifact[8000]=lgpow(fact[8000],MOD-2);
    for(int i=7999;i;i--)
        ifact[i]=(1LL*ifact[i+1]*(i+1))%MOD;
    fscanf(f,"%d %d %d %d",&N,&M,&H,&K);
    for(int i=0;i<=N;i++)
        for(int j=0;j<=M;j++)
            for(int k=0;k<=H;k++)
            {
                rez+=((i+j+k)%2==0 ? 1:-1)*((1LL*((1LL*C(N,i)*C(M,j))%MOD)*((1LL*C(H,k)*C((N-i)*(M-j)*(H-k),K))%MOD))%MOD);
                rez=(rez%MOD+MOD)%MOD;
            }
    fprintf(g,"%d",rez);
}
void sol2()
{
    ifact[0]=fact[0]=1;
    for(int i=1;i<=8000;i++)fact[i]=(1LL*fact[i-1]*i)%MOD;
    ifact[8000]=lgpow(fact[8000],MOD-2);
    for(int i=7999;i;i--)
        ifact[i]=(1LL*ifact[i+1]*(i+1))%MOD;
    fscanf(f,"%d %d %d %d",&N,&M,&H,&K);
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            for(int k=1;k<=H;k++)
                {for(int a=0;a<=i;a++)
                    for(int b=0;b<=j;b++)
                        for(int c=0;c<=k;c++)
                            dp[i][j][k]=(dp[i][j][k]+MOD-(1LL*((dp[i-a][j-b][k-c]*C(i,a))%MOD)*((1LL*C(j,b)*C(k,c))%MOD))%MOD)%MOD;dp[i][j][k]+=C(i*j*k,K);dp[i][j][k]%=MOD;}
    fprintf(g,"%d",dp[N][M][H]);
}
int main()
{
    sol1();
    fclose(f);
    fclose(g);
    return 0;
}
