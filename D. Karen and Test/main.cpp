#include <iostream>
#include <cstdio>
#define MOD 1000000007
using namespace std;
int F[105][200001],sz;
int tmp[105][200001];
int fa[200001];
int invfa[200001];
int N;
int V[200001];
int lgpow(int b,int e)
{
    int p=1;
    while(e)
    {
        if(e&1)p=(1LL*b*p)%MOD;
        b=(1LL*b*b)%MOD;
        e>>=1;
    }
    return p;
}
int compsign()
{
    return (1LL*(N-1+sz)*(N-sz)/2)%2==0 ? 1:-1;
}
void up()
{
    int sgn=compsign();
    for(int i=1;i<sz;i++)
    {
        for(int j=1;j<=N;j++)
        {tmp[i][j]=(F[i][j]+sgn*F[i+1][j])%MOD;}
        sgn*=-1;
    }
    for(int i=1;i<sz;i++)
        for(int j=1;j<=N;j++)
            F[i][j]=tmp[i][j];
    sz--;
}
int C(int N,int K)
{
    return (1LL*((1LL*fa[N]*invfa[K])%MOD)*invfa[N-K])%MOD;
}
int main()
{
    invfa[0]=fa[0]=1;
    for(int i=1;i<=200000;i++)fa[i]=(1LL*i*fa[i-1])%MOD;
    invfa[200000]=lgpow(fa[200000],MOD-2);
    for(int i=200000-1;i;i--)invfa[i]=(1LL*(i+1)*invfa[i+1])%MOD;
    cin>>N;
    for(int i=1;i<=N;i++)cin>>V[i];
    int tmp=(N/4)*4+1;if(tmp>N)tmp-=4;
    sz=N-tmp+1;
    for(int i=1;i<=sz;i++)
    {
        for(int j=i;j<=i+2*N/2;j++)
        {
            if((j-i)%2==1)continue;
            F[i][j]=C(tmp/2,(j-i)/2);
        }
    }
    while(sz>1)
        up();
    int rez=0;
    for(int i=1;i<=N;i++)
    {
        rez=(1LL*rez+1LL*F[1][i]*V[i])%MOD;
    }
    if(rez<0)rez=(rez%MOD+MOD)%MOD;
    cout<<rez;
    return 0;
}
