#include <iostream>
#define MOD 1000000007
using namespace std;
int fa[100005];
int ifa[100005];
int rez;
int lgpow(int b,int e)
{
    int p=1;
    while(e)
    {
        if(e&1)p=(1LL*b*p)%MOD;
        e>>=1;
        b=(1LL*b*b)%MOD;
    }
    return p;
}
int main()
{
    fa[0]=ifa[0]=1;
    for(int i=1;i<=100000;i++)fa[i]=(1LL*i*fa[i-1])%MOD;ifa[100000]=lgpow(fa[100000],MOD-2);
    for(int i=100000-1;i;i--)ifa[i]=(1LL*(i+1)*ifa[i+1])%MOD;
    int T,x,y;
    cin>>T;
    while(T--)
    {
        cin>>x>>y;
        x--;
        cout<<(2LL*fa[x]*((1LL*ifa[y]*ifa[x-y])%MOD))%MOD<<"\n";
    }
    return 0;
}
