#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;
vector<int> G[100005];
vector<int> GN[100005];
set<int> C[100005];
map<pair<int,int> ,int> L;
map<pair<int,int> ,int> R;
map<pair<int,int> ,int> sbpl;
vector<pair<int,int> > B;
int N,M,P;
int low[100005];
int dist[100005];
int T[100005];
char rez[100005];
void dfs(int nod,int tata)
{
    low[nod]=dist[nod];
    for(auto it:G[nod])
    {
        if(!dist[it])
        {
            dist[it]=1+dist[nod];
            dfs(it,nod);
            low[nod]=min(low[nod],low[it]);
            if(low[it]<=dist[nod]||sbpl[{nod,it}]>1)GN[nod].push_back(it);
            else B.push_back({nod,it});
        }
        if(tata!=it||sbpl[{nod,it}]>1)
        {
            low[nod]=min(dist[it],low[nod]);
        }
    }
}
int fi(int nod)
{
    if(T[nod]<0)return nod;
    return T[nod]=fi(T[nod]);
}
void u(int x,int y)
{
    x=fi(x);
    y=fi(y);
    if(x==y)return ;
    if(T[x]>T[y]){T[y]+=T[x];T[x]=y;}
    else         {T[x]+=T[y];T[y]=x;}
}
int main() {
    cin>>N>>M;
    for(int i=1;i<=N;i++)T[i]=-1;
    for(int i=1;i<=M;i++)
    {
        int x,y;
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
        L[{x,y}]=i;
        R[{y,x}]=i;
        sbpl[{x,y}]++;
        sbpl[{y,x}]++;
    }
    dist[1]=1;
    dfs(1,0);
    for(int i=1;i<=N;i++)
    {
        for(auto it:GN[i])
            u(i,it);
    }
    cin>>P;
    for(int i=1;i<=P;i++)
    {
        int x,y;
        cin>>x>>y;
        x=fi(x);
        y=fi(y);
        if(x!=y)
        {
            C[x].insert(y);
        }
    }
    for(auto it:B)
    {
        int x,y;
        x=fi(it.first);
        y=fi(it.second);
        if(C[x].find(y)!=C[x].end())
        {
            C[x].erase(y);
            u(x,y);
            if(L[{it.first,it.second}])
                rez[L[{it.first,it.second}]]='L';
            else
                rez[R[{it.first,it.second}]]='R';
        }
        else if(C[y].find(x)!=C[y].end())
        {
            C[y].erase(x);
            u(x,y);
            if(L[{it.first,it.second}])
                rez[L[{it.first,it.second}]]='L';
            else
                rez[R[{it.first,it.second}]]='R';
        }
    }
    for(int i=1;i<=M;i++)
        if(rez[i]=='\0')
            rez[i]='B';
    cout<<rez+1;
    return 0;
}
