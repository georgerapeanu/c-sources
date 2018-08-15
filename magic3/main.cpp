#include <cstdio>
using namespace std;
FILE *f=fopen("magic3.in","r");
FILE *g=fopen("magic3.out","w");
int N,C,P;
long long lgput(long long b,long long e)
{
    long long p=1;
    while(e)
    {
        if(e&1) p=(b*p)%P;
        b=(b*b)%P;
        e>>=1;
    }
    return p;
}
int main()
{
    fscanf(f,"%d%d%d",&C,&N,&P);
    if(lgput(C,N-1))
        fprintf(g,"%lld",lgput(C,N-1));
    else
        fprintf(g,"%d",P);
    fclose(f);
    fclose(g);
    return 0;
}
