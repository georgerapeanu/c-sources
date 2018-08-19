#include <cstdio>
using namespace std;
FILE *f=fopen("ackermann.in","r");
FILE *g=fopen("ackermann.out","w");
int T,N,M,MOD;
///mersi alex :D
int getphi(int nr)
{
    int phi=nr;
    for(int i=2;1LL*i*i<=nr;i++)
    {
        if(nr%i==0)
        {
            while(nr%i==0)nr/=i;
            phi=phi/i*(i-1);
        }
    }
    if(nr!=1)phi=phi/nr*(nr-1);
    return phi;
}
int lgpow(int b,int e,int MOD)
{
    int p=1;
    while(e)
    {
        if(e&1){p=(1LL*b*p)%MOD;}
        b=(1LL*b*b)%MOD;
        e>>=1;
    }
    return p;
}
int compute(int a,int b,int p)
{
    if(p<=1)return 1;
    if(b==1)return a;
    return lgpow(a,compute(a,b-1,getphi(p)),p);
}
int main()
{
    fscanf(f,"%d",&T);
    while(T--)
    {
        fscanf(f,"%d%d%d",&N,&M,&MOD);
        fprintf(g,"%d\n",compute(N,M,MOD));
    }
    fclose(f);
    fclose(g);
    return 0;
}
