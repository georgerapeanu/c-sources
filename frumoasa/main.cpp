#include <cstdio>
#define MOD 1000000007
using namespace std;
FILE *f=fopen("frumoasa.in","r");
FILE *g=fopen("frumoasa.out","w");
long long N,P,sol;
long long lgpow(long long b,long long e)
{
    long long rez=1;
    while(e)
    {
        if(e&1) rez=(rez*b)%MOD;
        b=(b*b)%MOD;
        e>>=1;
    }
    return rez;
}
int main()
{
    fscanf(f,"%lld %lld",&N,&P);
    if(P>26){fputc('0',g);return 0;}
    sol=1;
    for(int i=26-P+1;i<=26;i++) sol=(sol*i)%MOD;
    sol=(sol*lgpow(26-P,N-P))%MOD;
    fprintf(g,"%lld",sol);
    fclose(f);
    fclose(g);
    return 0;
}
