#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
FILE *f=fopen("ordini.in","r");
FILE *g=fopen("ordini.out","w");
int MOD,phi,F[1005];
int fr[10];
void getphi(int val)
{
    phi=val;
    F[0]=0;
    for(int i=2;i*i<=val;i++)
    {
        if(val%i==0)
        {
            F[++F[0]]=i;
            phi=phi/i*(i-1);
            while(val%i==0)val/=i;
        }
    }
    if(val!=1)
    {
        phi=phi/val*(val-1);
        F[++F[0]]=val;
    }
}
int lgpow(int b,int e)
{
    int p=1;
    while(e)
    {
        if(e&1)p=(1LL*p*b)%MOD;
        b=(1LL*b*b)%MOD;
        e>>=1;
    }
    return p;
}
struct inverse
{
    int E[1005],val;
    inverse()
    {
        val=0;memset(E,0,sizeof(E));
    }
    inverse(int nr)
    {
        val=nr;memset(E,0,sizeof(E));
        for(int i=1;i<=F[0];i++)
        {
            while(val%F[i]==0)
            {
                E[i]++;
                val/=F[i];
            }
        }
    }
    inverse operator *(inverse other)
    {
        inverse tmp;
        for(int i=1;i<=F[0];i++)
            tmp.E[i]=E[i]+other.E[i];
        tmp.val=(1LL*val*other.val)%MOD;
        return tmp;
    }
    inverse operator /(inverse other)
    {
        inverse tmp;
        for(int i=1;i<=F[0];i++)
            tmp.E[i]=E[i]-other.E[i];
        tmp.val=(1LL*val*lgpow(other.val,phi-1))%MOD;
        return tmp;
    }
    int toint()
    {
       int rez=val;
       for(int i=1;i<=F[0];i++)
            rez=(1LL*rez*lgpow(F[i],E[i]))%MOD;
       return rez;
    }
};
inverse fact[1005];
int nr(int nrcf)
{
    int rez=0;
    for(int i=1;i<=nrcf;i++)
        rez=(rez*10+1)%MOD;
    return rez;
}
int nrcf;
int solve(int C)
{
    nrcf=0;
    int rez=0;
    for(int i=0;i<=9;i++)nrcf+=fr[i];
    inverse tmp=fact[nrcf-1];
    for(int i=0;i<=9;i++)tmp=tmp/fact[fr[i]];
    for(int i=0;i<=9;i++)
    {
        if(fr[i]==0)continue;
        inverse t=tmp*inverse(fr[i]);
        rez=(rez+(1LL*t.toint()*i))%MOD;
    }
    tmp=tmp*inverse(nrcf);
    return (1LL*rez*nr(nrcf)+1LL*lgpow(10,nrcf)*C*tmp.toint())%MOD;
}
int main()
{
    for(int i=0;i<=9;i++)fscanf(f,"%d",&fr[i]);
    fscanf(f,"%d",&MOD);
    getphi(MOD);
    fact[0]=inverse(1);
    for(int i=1;i<=1000;i++)
        fact[i]=fact[i-1]*inverse(i);
    int rez=0;
    for(int i=1;i<=9;i++)
    {
        if(!fr[i])continue;
        fr[i]--;
        rez=(0LL+rez+solve(i))%MOD;
        fr[i]++;
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
