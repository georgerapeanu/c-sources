#include <iostream>
#include <vector>
using namespace std;
int d[300005];
int sum;
int pos=0;
int N,M;
vector<pair<int,int> > G[300005];
bool viz[300005];
bool U[300005];
void dfs(int nod,int tata,int edge)
{
    viz[nod]=1;
    for(auto it:G[nod])
    {
        if(!viz[it.first])
        {
            dfs(it.first,nod,it.second);
        }
    }
    if(d[nod])
    {
        d[tata]^=1;
        d[nod]^=1;
        U[edge]=1;
    }
}
int main()
{
    cin>>N>>M;
    for(int i=1;i<=N;i++)
    {
        cin>>d[i];
        if(d[i]==-1)
        {
            pos=i;
        }
        else
        {
            sum^=d[i];
        }
    }
    if(sum&&!pos)
    {
        cout<<-1;
        return 0;
    }
    if(sum==1)d[pos]=1;
    for(int i=1;i<=N;i++)d[i]=max(0,d[i]);
    for(int i=1;i<=M;i++)
    {
        int x,y;
        cin>>x>>y;
        G[x].push_back({y,i});
        G[y].push_back({x,i});
    }
    dfs(1,0,0);
    int nr=0;
    for(int i=1;i<=M;i++)nr+=U[i];
    cout<<nr<<"\n";
    for(int i=1;i<=M;i++)if(U[i])cout<<i<<"\n";
    return 0;
}
