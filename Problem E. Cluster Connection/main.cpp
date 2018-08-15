#include <iostream>
#define MOD 1000000007LL
using namespace std;
long long fact[1005];
long long ifact[1005];
long long lgpow(long long b,long long e)
{
    long long p=1;
    while(e)
    {
        if(e&1)p=(1LL*p*b)%MOD;
        b=(1LL*b*b)%MOD;
        e>>=1;
    }
    return p;
}
long long A(long long N,long long K)
{
    return (1LL*fact[N]*ifact[N-K])%MOD;
}
long long N;
int main()
{
    fact[0]=ifact[0]=1;
    for(int i=1;i<=1000;i++)fact[i]=(1LL*i*fact[i-1])%MOD;ifact[1000]=lgpow(fact[1000],MOD-2);
    for(int i=999;i;i--)ifact[i]=(1LL*ifact[i+1]*(i+1))%MOD;
    cin>>N;
    long long rez=1LL*((1LL*(1LL*(1LL*fact[N]*(N-4)%MOD)*ifact[2]%MOD)*ifact[2])%MOD)*ifact[2]%MOD;
    for(long long a=0;a<=N-2;a++)
    {
        for(long long b=a;b<=N-2-a;b++)
        {
            long long c=N-2-a-b;
            if(0<=a&&a<b&&b<c)rez=(rez+((((((((N*(N-1)*lgpow(ifact[2],1))%MOD)*A(N-2,a))%MOD)*A(N-2-a,b))%MOD)*fact[c])%MOD))%MOD;
            else if(0<a&&a==b&&b<c)rez=(rez+((((((((N*(N-1)*lgpow(ifact[2],2))%MOD)*A(N-2,a))%MOD)*A(N-2-a,b))%MOD)*fact[c])%MOD))%MOD;
            else if(0<=a&&a<b&&b==c)rez=(rez+((((((((N*(N-1)*lgpow(ifact[2],2))%MOD)*A(N-2,a))%MOD)*A(N-2-a,b))%MOD)*fact[c])%MOD))%MOD;
            else if(0<a&&a==b&&b==c)rez=(rez+((((((((((N*(N-1)*lgpow(ifact[2],2))%MOD)*ifact[3]%MOD)*fact[2]%MOD)*A(N-2,a))%MOD)*A(N-2-a,b))%MOD)*fact[c])%MOD))%MOD;
        }
    }
    cout<<rez;
    return 0;
}
