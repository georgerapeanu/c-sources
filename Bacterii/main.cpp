#include <cstdio>
using namespace std;
FILE *f=fopen("bacterii.in","r");
FILE *g=fopen("bacterii.out","w");
long long lgpow(long long b,long long e,long long MOD)
{
    long long p=1;
    while(e)
    {
        if(e&1)p=(1LL*p*b)%MOD;
        b=(1LL*b*b)%MOD;
        e>>=1;
    }
    return p;
}
long long N,K,M,T;
int main()
{
    fscanf(f,"%lld",&T);
    while(T--)
    {
        fscanf(f,"%lld %lld %lld",&N,&K,&M);
        if((N-1)%M==0){fprintf(g,"1\n");continue;}
        long long e=lgpow(2,K,M-1);
        if(e==0){fprintf(g,"2\n");continue;}
        fprintf(g,"%lld\n",(lgpow((N-1)%M,e,M)+1)%M);
    }
    fclose(f);
    fclose(g);
    return 0;
}
