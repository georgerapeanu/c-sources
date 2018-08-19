#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
#define MOD 1000000007
#define mp make_pair
using namespace std;
FILE *f=fopen("vagoane.in","r");
FILE *g=fopen("vagoane.out","w");
int N,M,C;
int V[100005];
int fact[100005];
int inv[100005];
int ans=1;
vector<pair<int,int> > Ev;
multiset <int> S;
int lgpow(int b,int e)
{
    if(!e) return b;
    if(e&1) return (1LL*b*lgpow((1LL*b*b)%MOD,e>>1))%MOD;
    return lgpow((1LL*b*b)%MOD,e>>1);
}
int main()
{
    fscanf(f,"%d %d %d",&N,&M,&C);
    inv[0]=fact[0]=1;
    for(int i=1;i<=C;i++)
    {
        fact[i]=(1LL*i*fact[i-1])%MOD;
        inv[i]=lgpow(fact[i],MOD-2);
    }
    for(int i=1;i<=M;i++)
    {
        int a,b;
        fscanf(f,"%d %d",&a,&b);
        Ev.push_back(mp(a,a));
        Ev.push_back(mp(b+1,-a));
    }
    sort(Ev.begin(),Ev.end());
    int u=1,poz=0;
    while(poz<Ev.size())
    {
        while(poz+1<Ev.size()&&Ev[poz].first==Ev[poz+1].first)
        {
            if(Ev[poz].second<0) S.erase(S.find(-Ev[poz].second));
            else S.insert(Ev[poz].second);
            poz++;
        }
        if(Ev[poz].second<0) S.erase(S.find(-Ev[poz].second));
        else S.insert(Ev[poz].second);
        if(S.size()==0)
        {
            ans=(1LL*ans*(Ev[poz].second-u>C ? 0:(1LL*fact[C]*inv[C-Ev[poz].second+u+1])%MOD))%MOD;
        }
        poz++;
    }
    if(u<=N)
        ans=(1LL*ans*(N+1-u>C ? 0:(1LL*fact[C]*inv[C-N+u])%MOD));
    fprintf(g,"%d",ans);
    fclose(f);
    fclose(g);
    return 0;
}
