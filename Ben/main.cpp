#include <cstdio>
#include <algorithm>
#define MOD 32173
using namespace std;
FILE *f=fopen("ben.in","r");
FILE *g=fopen("ben.out","w");
int N;
int st,dr;
int in[30005];
int out[30005];
int fact[30005];
int ifact[30005];
int act=0;
int rez=1;
int K;
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
int A(int N,int K)
{
    return (1LL*fact[N]*ifact[N-K]%MOD);
}
int main()
{
    fscanf(f,"%d",&N);
    fact[0]=1;
    ifact[0]=1;
    for(int i=1;i<=30000;i++)fact[i]=(1LL*i*fact[i-1])%MOD;ifact[30000]=lgpow(fact[30000],MOD-2);
    for(int i=30000-1;i;i--)ifact[i]=(1LL*(i+1)*ifact[i+1])%MOD;
    for(int i=1;i<=N;i++)
    {
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        in[x]++;
        out[y]++;
    }
    for(int i=1;i<=30000;i++)
    {
        act+=in[i];
        K=max(K,act);
        act-=out[i];
    }
    act=0;
    for(int i=1;i<=30000;i++)
    {
        rez=(1LL*rez*A(K-act,in[i]))%MOD;
        act-=out[i];
        act+=in[i];
    }
    fprintf(g,"%d %d",K,rez);
    fclose(f);
    fclose(g);
    return 0;
}
