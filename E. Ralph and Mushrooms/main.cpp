#include <iostream>
#include <vector>
using namespace std;
int x[1000005],y[1000005],w[1000005];
vector<int> G[1000005];
vector<pair<int,int> > g[1000005];
int low[1000005];
int st[1000005],len;
int id[1000005];
bool inst[1000005];
int ctc[1000005],cnt;
int lastid,N,M,s;
long long dp[1000005];
bool calcdp[1000005];
long long W[1000005];
void tarjan(int nod)
{
    id[nod]=low[nod]=++lastid;
    st[++len]=nod;inst[nod]=1;
    for(auto it:G[nod])
    {
        if(!id[it])tarjan(it);
        if(inst[it])low[nod]=min(low[nod],low[it]);
    }
    if(low[nod]==id[nod])
    {
        cnt++;
        while(st[len]!=nod)
        {
            ctc[st[len]]=cnt;
            inst[st[len]]=0;
            len--;
        }
        ctc[st[len]]=cnt;
        inst[st[len]]=0;
        len--;
    }
}
void getdp(int nod)
{
    if(calcdp[nod])return;
    calcdp[nod]=1;
    dp[nod]=W[nod];
    for(auto it:g[nod])
    {
        getdp(it.first);
        dp[nod]=max(dp[nod],dp[it.first]+W[nod]+it.second);
    }
}
int main()
{
    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);
    cin>>N>>M;
    for(int i=1;i<=M;i++)
    {
        cin>>x[i]>>y[i]>>w[i];
        G[x[i]].push_back(y[i]);
    }
    cin>>s;
    for(int i=1;i<=N;i++)
        if(!id[i])
            tarjan(i);
    for(int i=1;i<=M;i++)
    {
        if(ctc[x[i]]==ctc[y[i]])
        {
            int st=-1,dr=20000;
            while(dr-st>1)
            {
                int mid=(st+dr)/2;
                if(mid*(mid+1)/2<=w[i])
                    st=mid;
                else
                    dr=mid;
            }
            W[ctc[x[i]]]+=1LL*(st+1)*w[i]-(1LL*st*(st+1)*(2*st+1)/6+1LL*st*(st+1)/2)/2;
        }
        else
        {
            g[ctc[x[i]]].push_back({ctc[y[i]],w[i]});
        }
    }
    for(int i=1;i<=N;i++)
        if(!calcdp[ctc[i]])
            getdp(ctc[i]);
    cout<<dp[ctc[s]];
    return 0;
}
