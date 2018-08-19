#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <vector>
#include <cstdlib>
using namespace std;
int N;
vector<int> G[200005];
vector<int> Gt[200005];
bool viz[200005];
int dist[200005];
int gr[200005];
int nxt[200005];
bool U[200005];
int  V[200005];
vector<int> ord;
queue<int> Q;
int mex(int nod)
{
    int mex=0;
    while(U[mex])mex++;
    for(auto it:G[nod])U[V[it]]=0;
    return mex;
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        int x=i,y;
        cin>>y;
        G[y].push_back(x);
        Gt[x].push_back(y);
        gr[y]++;
    }
    for(int i=1;i<=N;i++)
    {
        if(!gr[i])Q.push(i);
    }
    while(!Q.empty())
    {
        int nod=Q.front();Q.pop();
        for(auto it:Gt[nod])
        {
            gr[it]--;
            if(!gr[it])
                Q.push(it);
        }
        ord.push_back(nod);
    }
    for(auto it:ord)
    {
        for(auto it2:G[it])
            if(!gr[it2])
                U[V[it2]]=1;
        V[it]=mex(it);
    }
    int len=0;
    for(int i=1;i<=N;i++)
    {
        if(gr[i])
        {
            len++;
            for(auto it2:G[i])
                if(!gr[it2])
                    U[V[it2]]=1;
            V[i]=mex(i);
        }
    }
    int nr=0;
    for(int i=1;i<=N;i++)
    {
        if(gr[i])
        {
            if(!U[V[i]])nr++;
            U[V[i]]=1;
        }
    }
    if(nr>=2||len%2==0)cout<<"POSSIBLE";
    else cout<<"IMPOSSIBLE";
    return 0;
}
