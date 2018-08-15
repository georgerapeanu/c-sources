#include <cstdio>
#define MOD 10007
using namespace std;
FILE *f=fopen("matrice5.in","r");
FILE *g=fopen("matrice5.out","w");
long long N,M,K,P;
int T;
long long logp(long long b,long long e)
{
    long long p=1;
    while(e)
    {
        if(e&1)
            p=(p*b)%MOD;
        e/=2;
        b=(b*b)%MOD;
    }
    return p;
}
int main()
{
    fscanf(f,"%d",&T);
    while(T--)
    {
        fscanf(f,"%lld %lld %lld %lld",&N,&M,&P,&K);
        fprintf(g,"%lld\n",(logp(K,(N-1)*(M-1))*logp(P,N*M))%MOD);
    }
    fclose(f);
    fclose(g);
    return 0;
}
