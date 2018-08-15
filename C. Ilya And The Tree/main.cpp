#include <iostream>
#include <vector>
using namespace std;
vector<int> G[200005];
vector<int> D[200005];
int ans[200005];
int N;
int x,y;
int V[200005];
int cnt[200005];
int gcd(int a,int b)
{
    if(!b)return a;
    return gcd(b,a%b);
}
void dfs(int nod,int tata,int lvl)
{
    for(auto it:D[V[nod]])
    {
        cnt[it]++;
        if(cnt[it]>=lvl-1)ans[nod]=max(it,ans[nod]);
    }
    for(auto it:G[nod])if(it!=tata)dfs(it,nod,lvl+1);
    for(auto it:D[V[nod]])
    {
        cnt[it]--;
    }
    if(tata)
    {
        for(auto it:D[V[tata]])
            if(cnt[it]>=lvl-1)
                ans[nod]=max(ans[nod],it);
    }
}
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    for(int i=1;i<=200000;i++)for(int j=i;j<=200000;j+=i)D[j].push_back(i);
    cin>>N;
    for(int i=1;i<=N;i++)cin>>V[i];
    for(int i=1;i<N;i++)
    {
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(1,0,1);
    for(int i=1;i<=N;i++)cout<<ans[i]<<" ";
    return 0;
}
