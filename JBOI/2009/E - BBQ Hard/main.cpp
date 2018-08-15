#include <iostream>
#define MOD 1000000007
using namespace std;
pair<int,int> V[200005];
bool cmp(pair<int,int> a,pair<int,int> b)
{
    return a.first+a.second<b.first+b.second;
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
int fact[10005];
int inv[10005];
int frecv[4005];
int N;
int rez;
int c,d;
void eval()
{
    rez=0;
    for(int i=1;i<=4000;i++)
    {
        rez=(rez+(1LL*frecv[i]*((1LL*fact[c+i]*inv[c])%MOD))%MOD)%MOD;
    }
}
void scoate(int d)
{
    rez=((rez-1LL*fact[c+d]*inv[c])%MOD+MOD)%MOD;
    frecv[d]--;
}
void creste(int x)
{

}
int main()
{
    fact[0]=inv[0]=1;
    for(int i=1;i<=10000;i++)fact[i]=(1LL*fact[i-1]*i)%MOD;inv[10000]=lgpow(fact[10000],MOD-2);
    for(int i=9999;i;i--)inv[i]=(1LL*inv[i+1]*(i+1))%MOD;
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i].first>>V[i].second;
        frecv[V[i].first+V[i].second]++;
    }
    sort(V+1,V+1+N,cmp);
    c=0;
    eval();
    return 0;
}
