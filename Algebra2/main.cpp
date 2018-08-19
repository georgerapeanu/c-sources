#include <cstdio>
#define MOD 1000000009
using namespace std;
FILE *f=fopen("algebra2.in","r");
FILE *g=fopen("algebra2.out","w");
long long N;
long long x,y;
long long lgpow(long long b,long long e)
{
    long long p=1;
    while(e)
    {
        if(e&1) p=(p*b)%MOD;
        b=(b*b)%MOD;
        e>>=1;
    }
    return p;
}
int main()
{
    fscanf(f,"%lld",&N);
    x=N;y=N+1;
    if(N%2) y/=2;
    else x/=2;
    N%=MOD;
    fprintf(g,"%lld",lgpow(lgpow(N,x),y));
    fclose(f);
    fclose(g);
    return 0;
}
