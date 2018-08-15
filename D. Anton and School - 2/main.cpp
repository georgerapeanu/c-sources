#include <iostream>
#define MOD 1000000007
#define NMAX 200000
using namespace std;
int ppoz[NMAX+5];
char a[NMAX+5];
int inv[NMAX+5];
int fact[NMAX+5];
int nrdupa[NMAX+5];
int nrinainte[NMAX+5];
int N;
int lgpow(int b,int e)
{
    int p=1;
    while(e)
    {
        if(e&1)
            p=(1LL*b*p)%MOD;
        b=(1LL*b*b)%MOD;
        e>>=1;
    }
    return b;
}
int C(int n,int k)
{
    return (1LL*((1LL*fact[n]*inv[k])%MOD)*inv[n-k])%MOD;
}
int main()
{
    fact[0]=1;
    for(int i=1;i<=NMAX;i++)
    {
        fact[i]=(1LL*i*fact[i-1])%MOD;
        inv[i]=lgpow(fact[i],MOD-2);
    }
    cin.getline(a+1,NMAX+4);
    N=strlen(a+1);
    N-=(a[N]=='\n');
    int upoz=N+1;
    for(int i=N;i;i--)
    {
        ppoz[i]=upoz;
        nrdupa[i]=nrdupa[i+1]+(a[i+1]==')');
        if(a[i]==')')
            upoz=i;
    }
    for(int i=1;i<=N;i++)
    {

    }
    return 0;
}
