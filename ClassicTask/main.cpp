#include <cstdio>
#define LL long long
using namespace std;
FILE *f=fopen("classictask.in","r");
FILE *g=fopen("classictask.out","w");
LL A,B,C;
void mul(LL &a,LL b)
{
    LL p=0;
    while(b)
    {
        if(b&1)p=(p+a)%C;
        b>>=1;
        a=(a+a)%C;
    }
    a=p;
}
LL lgpow(LL b,LL e)
{
    LL p=1;
    while(e)
    {
        if(e&1)
            mul(p,b);
        mul(b,b);
        e>>=1;
    }
    return p;
}
int main()
{
    fscanf(f,"%lld%lld%lld",&A,&B,&C);
    fprintf(g,"%lld",lgpow(A,B));
    fclose(f);
    fclose(g);
    return 0;
}
