#include <cstdio>
using namespace std;
int N,M;
int P;
FILE *f=fopen("gcd.in","r");
FILE *g=fopen("gcd.out","w");
int  lgpow(int b,int e)
{
    int p=1;
    while(e)
    {
        if(e&1) p=(1LL*p*b)%P;
        b=(1LL*b*b)%P;
        e>>=1;
    }
    return p;
}
int gcd(int a,int b)
{
    if(!b) return a;
    return gcd(b,a%b);
}
int main()
{
    int T;
    fscanf(f,"%d",&T);
    while(T)
    {
        fscanf(f,"%d%d%d",&N,&M,&P);
        fprintf(g,"%d\n",lgpow(2,gcd(N,M))-1);
        T--;
    }
    fclose(f);
    fclose(g);
    return 0;
}
