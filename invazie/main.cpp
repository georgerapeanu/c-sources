#include <cstdio>
#define LL long long
#define MOD 666013
using namespace std;
FILE *f=fopen("invazie.in","r");
FILE *g=fopen("invazie.out","w");
LL suma,dif;
long long N,K,P;
int T;
LL lgpow(LL exp,LL b)
{
    LL p=1;
    while(exp)
    {
        if(exp&1)
            p=(p*b)%MOD;
        b=(b*b)%MOD;
        exp/=2;
    }
    return p;
}
int main()
{
    fscanf(f,"%d",&T);
    for(int i=1;i<=T;i++)
    {
        fscanf(f,"%lld %lld %lld",&K,&P,&N);
        suma=lgpow(N,(K+P)%MOD);
        dif=lgpow(N,(K-P)%MOD);
        if(dif<0)
            dif+=MOD;
        suma=(suma+dif)%MOD;
        suma=(suma*333007)%MOD;
        fprintf(g,"%lld\n",suma);
    }
    fclose(f);
    fclose(g);
    return 0;
}
