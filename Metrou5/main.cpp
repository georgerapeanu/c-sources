#include <cstdio>
#define MOD 1000000007
#define LIM 200000
using namespace std;
FILE *f=fopen("metrou5.in","r");
FILE *g=fopen("metrou5.out","w");
int fa[LIM+5];
int invfa[LIM+5];
int N,V[LIM+5],K;
int uval,upos;
int rez=1;
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
int C(int N,int K)
{
    return (1LL*((1LL*fa[N]*invfa[K])%MOD)*invfa[N-K])%MOD;
}
int main()
{
    invfa[0]=fa[0]=1;
    for(int i=1;i<=LIM;i++)fa[i]=(1LL*i*fa[i-1])%MOD;
    invfa[LIM]=lgpow(fa[LIM],MOD-2);
    for(int i=LIM-1;i;i--)invfa[i]=(1LL*(i+1)*invfa[i+1])%MOD;
    fscanf(f,"%d %d",&N,&K);
    for(int i=1;i<=N;i++)fscanf(f,"%d",&V[i]);
    uval=V[0]=1;
    V[N+1]=K;
    for(int i=1;i<=N+1;i++)
    {
        if(V[i]!=-1)
        {
            if(uval>V[i]){rez=0;break;}
            rez=(1LL*rez*C((V[i]-uval)+(i-upos-1),V[i]-uval))%MOD;
            upos=i;
            uval=V[i];
        }
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
