#include <iostream>
#define MOD 1000000007
#define MAXN 1000000
using namespace std;
int N,K;
int s[MAXN+5];
int S[MAXN+5];
int fact[MAXN+5];
int ifact[MAXN+5];
int add(int a,int b)
{
    a+=b;
    if(a>=MOD)a-=MOD;
    return a;
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
int lgpow(int b,int e)
{
    int p=1;
    while(e)
    {
        if(e&1)p=mult(p,b);
        b=mult(b,b);
        e>>=1;
    }
    return p;
}
int main()
{
    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);
    fact[0]=1;for(int i=1;i<=MAXN;i++)fact[i]=mult(fact[i-1],i);
    ifact[MAXN]=lgpow(fact[MAXN],MOD-2);for(int i=MAXN-1;i>=0;i--)ifact[i]=mult(ifact[i+1],i+1);
    cin>>N>>K;
    s[0]=S[0]=1;
    int sum=1,sum2=0;
    for(int i=1;i<=N;i++)
    {
        S[i]=sum;
        s[i]=S[i];
        if(0<=max(0,i+1-K)-2)
        {
            sum2=add(sum2,mult(s[max(0,i+1-K)-2],mult(fact[i-1],ifact[max(0,i+1-K)-2])));
            s[i]=scad(s[i],sum2);
        }
        sum=add(mult(sum,i),s[i]);
        sum2=mult(sum2,i);
    }
    cout<<scad(fact[N],S[N]);
    return 0;
}
