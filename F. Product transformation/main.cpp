#include <iostream>
using namespace std;
int Q,a,M,N;
int fact[3000005];
int ifact[3000005];
int C(int N,int K)
{
    return (1LL*((1LL*fact[N]*ifact[K])%(Q-1))*ifact[N-K])%(Q-1);
}
int lgpow(int b,int e,int Q)
{
    int p=1;
    while(e)
    {
        if(e&1)p=(1LL*p*b)%Q;
        b=(1LL*b*b)%Q;
        e>>=1;
    }
    return p;
}
int phi(int Q)
{
    int phi=Q;
    for(int i=2;1LL*i*i<=Q;i++)
    {
        if(Q%i==0)
        {
            phi=(phi/i)*(i-1);
            while(Q%i==0)Q/=i;
        }
    }
    if(Q!=1)phi=(phi/Q)*(Q-1);
    return phi;
}
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N>>M>>a>>Q;
    fact[0]=1;
    for(int i=1;i<=3000000;i++)fact[i]=(1LL*i*fact[i-1])%(Q-1);ifact[3000000]=lgpow(fact[3000000],phi(Q-1)-1,Q-1);
    for(int i=3000000-1;i>=0;i--)ifact[i]=(1LL*(i+1)*ifact[i+1])%(Q-1);
    for(int i=1;i<=N;i++)
    {
        cout<<lgpow(a,C(M+N-i,M),Q)<<" ";
    }
    return 0;
}
