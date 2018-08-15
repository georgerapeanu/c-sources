#include <iostream>
#include <vector>
#include <queue>
using namespace std;
vector<int> G[200005];
int lvl[200005];
int N,x;
int a,b,rez;
int dist[200005];
void dfs(int nod,int nvl,int tata)
{
    lvl[nod]=nvl;
    for(auto it:G[nod])
        if(it!=tata)dfs(it,nvl+1,nod);
}
queue<int> Q;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N>>x;
    for(int i=1;i<N;i++)
    {
        cin>>a>>b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    dfs(1,0,0);
    dist[x]=0;
    Q.push(x);
    while(!Q.empty())
    {
        int nod=Q.front();Q.pop();
        if(lvl[nod]<=dist[nod])continue;
        rez=max(rez,2*lvl[nod]);
        for(auto it:G[nod])
            if(!dist[it]&&it!=x)
            {
                dist[it]=dist[nod]+1;
                Q.push(it);
            }
    }
    cout<<rez;
    return 0;
}
