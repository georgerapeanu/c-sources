#include <iostream>
#include <cmath>
#include <algorithm>
#define x first
#define y second
#define MOD 1000000007
#define LIM 100000
#define EPS 1e-6
#define PI 3.1415926
using namespace std;
vector<pair<double,int> > Ev;
int N,K;
int nr;
int fa[LIM+5];
int invfa[LIM+5];
int rez=0;
pair<int,int> V[100005],P;
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
int C(int N,int K)
{
    if(K>N)return 0;
    return (1LL*((1LL*fa[N]*invfa[K])%MOD)*invfa[N-K])%MOD;
}
long long det(pair<int,int> a,pair<int,int> b,pair<int,int> c)
{
    return 1LL*a.x*b.y+1LL*b.x*c.y+1LL*c.x*a.y-1LL*a.x*c.y-1LL*b.x*a.y-1LL*c.x*b.y;
}
int dist(int x,int y)
{
    if(x<=y)return y-x+1;
    return N-x+1+y;
}
int main() {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N>>K;
    invfa[0]=fa[0]=1;
    for(int i=1;i<=N;i++)fa[i]=(1LL*i*fa[i-1])%MOD;
    invfa[N]=lgpow(fa[N],MOD-2);
    for(int i=N-1;i;i--)invfa[i]=(1LL*(i+1)*invfa[i+1])%MOD;
    for(int i=1;i<=N;i++)
    {
        nxt[i]=i+1;
        cin>>V[i].x>>V[i].y;
    }
    nxt[N]=1;
    cin>>P.x>>P.y;
    int dr=1;
    rez=C(N,K);
    for(int st=1;st<=N;st++)
    {
        while(det(V[st],P,V[nxt[dr]])<=0)dr=nxt[dr];
        rez-=C(dist(st,dr)-1,K-1);
        if(rez<0)rez+=MOD;
    }
    cout<<rez;
    return 0;
}
