#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define MOD 1000000007
using namespace std;
int fr[100005];
int D[100005];
int N,M;
int scad[100005];
vector<int> G[100005];
int rez=1;
int ceva[100005];
long long lgpow(long long b,long long e)
{
    long long p=1;
    while(e)
    {
        if(e&1)
        {
            p=(1LL*b*p)%MOD;
        }
        b=(1LL*b*b)%MOD;
        e>>=1;
    }
    return p;
}
int main() {
    cin>>N>>M;
    for(int i=1;i<=N;i++){cin>>D[i];if(D[i]==0&&i>1)rez=0;fr[D[i]]++;}
    for(int i=1;i<=M;i++)
    {
        int x,y;
        cin>>x>>y;
        if(D[x]-D[y]>=2||D[y]-D[x]>=2)rez=0;
        G[x].push_back(y);
        G[y].push_back(x);
        if(D[x]==D[y])scad[D[x]]++;
    }
    for(int i=1;i<N;i++)if(fr[i]&&!fr[i-1])rez=0;
    for(int i=2;i<=N;i++)
    {
        int nr=0;
        for(auto it:G[i])
            if(D[it]==D[i]-1)
                nr++;
        if(!nr)rez=(1LL*rez*(lgpow(2,fr[D[i]-1])-1))%MOD;
        else rez=(1LL*rez*lgpow(2,fr[D[i]-1]-nr))%MOD;
        rez=(1LL*rez*(lgpow(2,1LL*fr[i-1]*(fr[i-1]-1)/2-scad[i-1])))%MOD;
    }
    cout<<rez;
    return 0;
}
