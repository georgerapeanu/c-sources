#include <cstdio>
#define MOD 9901
using namespace std;
FILE *f=fopen("sumdiv.in","r");
FILE *g=fopen("sumdiv.out","w");
int P[500000];
long long E[500000];
int nr;
int N,B;
int lgpow(int b,long long e)
{
    int p=1;
    while(e)
    {
        if(e&1)p=(1LL*b*p)%MOD;
        b=(1LL*b*b)%MOD;
        e>>=1;
    }
    return p;
}
int scad(int a,int b)
{
    a-=b;
    if(a<0)a+=MOD;
    return a;
}
int mult(int a,int b)
{
    return 1LL*a*b%MOD;
}
int main()
{
    fscanf(f,"%d %d",&N,&B);
    if(!B){fprintf(g,"%d",1);return 0;}
    for(int i=2;1LL*i*i<=N;i++)
    {
        if(N%i==0)
        {
            P[++nr]=i;
            while(N%i==0)
            {
                N/=i;
                E[nr]+=B;
            }
        }
    }
    if(N!=1)
    {
        P[++nr]=N;
        E[nr]=B;
    }
    int rez=1;
    for(int i=1;i<=nr;i++)
    {
        P[i]%=MOD;
        if(P[i]==0)
        {
            ;
        }
        else if(P[i]==1)
        {
            rez=mult(rez,E[i]+1);
        }
        else
            rez=mult(rez,mult(scad(lgpow(P[i],E[i]+1),1),lgpow(P[i]-1,MOD-2)));
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
