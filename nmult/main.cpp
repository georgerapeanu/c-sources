#include <cstdio>
#define MOD 666013
#define NMAX 100005
using namespace std;
FILE *f=fopen("nmult.in","r");
FILE *g=fopen("nmult.out","w");
int inv1,inv2,fact,fact2;
int N,W,K;
/*
e clar ca sol(k,n,1) = C(n,k)
altfel transpui sirul in y,unde y[i]=x[i]-i+1
y[i]-y[i-1]=x[i]-i+1-x[i-1]+i-1-1=x[i]-x[i-1]-1>=w-1
y[k]=x[k]-k+1<=n-k+1
deci trebuie sa rezolvam acum acceasi problema pentru sirul y
*/
int lgpow(int b,int e)
{
    int p=1;
    while(e)
    {
        if(e&1) p=(1LL*p*b)%MOD;
        b=(1LL*b*b)%MOD;
        e>>=1;
    }
    return p;
}
int C(int N,int K)
{
    fact=1;
    for(int i=1;i<=N&&i<MOD;i++)
    {
        fact=(1LL*fact*i)%MOD;
        if(i==K) inv1=fact;
        if(i==N-K) inv2=fact;
    }
    fact2=1;
    if(inv1)
        inv1=lgpow(inv1,MOD-2);
    else
        inv1=lgpow(fact,MOD-2);
    if(inv2)
        inv2=lgpow(inv2,MOD-2);
    else
        inv2=lgpow(fact,MOD-2);
    if(N>=MOD&&K<MOD&&N-K<MOD)
        return 0;
    for(int i=MOD+1;i<=N;i++)
    {
        fact2=(1LL*fact2*i)%MOD;
        if(i==K) inv1=(1LL*lgpow(fact2,MOD-2)*inv1)%MOD;
        if(i==N-K) inv2=(1LL*lgpow(fact2,MOD-2)*inv2)%MOD;
    }
    return ((((1LL*fact*fact2)%MOD)*inv1)%MOD)*inv2%MOD;
}
int sol(int k,int n,int w)
{
    if(w==1)
        return C(n,k);
    else
        return sol(k,n-k+1,w-1);
}
int main()
{
    fscanf(f,"%d%d%d",&N,&K,&W);
    if(1LL*N>=1LL*(K-1)*W+1)
        fprintf(g,"%d",sol(K,N,W));
    else
        fputc('0',g);
    fclose(f);
    fclose(g);
    return 0;
}
