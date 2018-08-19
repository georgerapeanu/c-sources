#include <iostream>
#include <algorithm>
#define MOD 1000000007
using namespace std;
int N;
int X[300005];
int f;
int rez;
int lgpow(int b,int e)
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
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)cin>>X[i];
    sort(X+1,X+1+N);
    for(int i=2;i<=N;i++)
    {
        f=(2LL*(f+1LL*(X[i]-X[i-1])*(lgpow(2,i-2)-1))%MOD+X[i]-X[i-1])%MOD;
        if(f>=MOD)f-=MOD;
        rez+=f;
        if(rez>=MOD)rez-=MOD;
    }
    cout<<rez;
    return 0;
}
