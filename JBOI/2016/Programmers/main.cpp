#include <iostream>
#include <vector>
using namespace std;
vector<int> G[50005];
int nr=0;
int dist[50005];
bool viz[50005];
int V[50005];
int N,M;
int P,I;
int st=0;
bool dfs(int nod,int lvl)
{
    bool ok=0;
    if(V[nod]==1&&lvl%2==0)ok=1;
    dist[nod]=lvl;
    nr++;
    for(auto it:G[nod])
    {
        if(!dist[it])ok|=dfs(it,lvl+1);
        else if(dist[it]%2==lvl%2)ok|=1;
    }
    return ok;
}
void dfs2(int nod)
{
    P+=(dist[nod]%2==0);
    I+=(dist[nod]%2==1);
    viz[nod]=1;
    for(auto it:G[nod])
    {
        if(!viz[it])dfs2(it);
    }
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++){cin>>V[i];st+=V[i];}
    cin>>M;
    for(int i=1;i<=M;i++)
    {
        int x,y;
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for(int i=1;i<=N;i++)
    {
        if(!dist[i]&&V[i])
        {
            nr=0;
            bool tmp=dfs(i,1);
            if(nr==1);
            else if(tmp){P+=nr;I+=nr;}
            else dfs2(i);
        }
    }
    cout<<max(st,max(P,I));
    return 0;
}
