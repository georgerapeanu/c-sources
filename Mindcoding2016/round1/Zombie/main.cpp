#include <iostream>
#define MOD 666013
using namespace std;
int rez;
int f[100005];
int N,M;
int a,b;
int fact(int x)
{
    if(!f[x])
        f[x]=(1LL*x*fact(x-1))%MOD;
    return f[x];
}
int lgpow(int b,int e)
{
    int p=1;
    while(e)
    {
        if(e&1)
            p=(1LL*p*b)%MOD;
        b=(1LL*b*b)%MOD;
        e>>=1;
    }
    return p;
}
int comb(int N,int K)
{
    return (1LL*((1LL*fact(N)*lgpow(fact(K),MOD-2))%MOD)*lgpow(fact(N-K),MOD-2))%MOD;
}
int main()
{
    f[0]=1;
    cin>>N>>M;
    if(N<M)
        {cout<<0;return 0;}
    else
    {
        a=fact(M);
        b=lgpow(M,N);
        int sg=-1;
        for(int i=1;i<=M;i++)
        {
            a=((a+1LL*sg*comb(M,i)*fact(M-i))%MOD+MOD)%MOD;
            b=((b+1LL*sg*comb(M,i)*lgpow(M-i,N))%MOD+MOD)%MOD;
            sg*=-1;
        }
        cout<<(1LL*a*b)%MOD;
    }
    return 0;
}
