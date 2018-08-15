#include <iostream>
#define MOD 1000000007
using namespace std;
long long N,M,S;
long long lgpow(long long b,long long e)
{
    long long p=1;
    while(e)
    {
        if(e&1)p=1LL*p*b%MOD;
        b=1LL*b*b%MOD;
        e>>=1;
    }
    return p;
}
int main()
{
    cin>>N>>M>>S;
    if(N>M)swap(N,M);
    if(N==1)
    {
        if(M==1||S==1)cout<<1;
        else cout<<(M%2==1 ? 1:0);
    }
    else
    {
        if(N%2!=M%2&&S==-1)cout<<0;
        else cout<<lgpow(lgpow(2,M-1),N-1);
    }
    return 0;
}
