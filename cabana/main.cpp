#include <cstdio>
#define MOD 1000000007
#define VMAX 1000000
using namespace std;
FILE *f=fopen("cabana.in","r");
FILE *g=fopen("cabana.out","w");
int fact[1000005];
int T,K;
long long N;
int lgput(int b,long long e)
{
    int p=1;
    while(e)
    {
        if(e&1) p=(1LL*p*b)%MOD;
        e>>=1;
        b=(1LL*b*b)%MOD;
    }
    return p;
}
int main()
{
    fact[0]=1;
    for(int i=1;i<=VMAX;i++)
        fact[i]=(1LL*i*fact[i-1])%MOD;
    fscanf(f,"%d",&T);
    for(int i=1;i<=T;i++)
    {
        fscanf(f,"%lld %d",&N,&K);
        fprintf(g,"%lld\n",(1LL*lgput(fact[K],N/K+1)*lgput(fact[K-N%K],MOD-2))%MOD);
    }
    fclose(f);
    fclose(g);
    return 0;
}
