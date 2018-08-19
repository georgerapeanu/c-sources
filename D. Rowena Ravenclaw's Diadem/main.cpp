#include <iostream>
#include <vector>
using namespace std;
int N;
int p,t;
int T[18][100005];
bool SP[18][100005];
bool U[18][100005];
int lvl[100005];
vector<int> G[100005];
int P[100005];
int lca(int u,int v)
{
    if(lvl[u]>lvl[v])swap(u,v);
    for(int i=17;i>=0;i--)
    {
        if(lvl[v]-lvl[u]>=(1<<i))
        {
            v=T[i][v];
        }
    }
    if(u==v)return u;
    for(int i=17;i>=0;i--)
    {
        if(T[i][u]!=T[i][v])
        {
            u=T[i][u];
            v=T[i][v];
        }
    }
    return T[0][u];
}
bool sp(int u,int v)
{
    if(lvl[u]>lvl[v])swap(u,v);
    for(int i=17;i>=0;i--)
    {
        if(lvl[v]-lvl[u]>=(1<<i))
        {
            if(SP[i][v])
            {
                v=T[i][v];
            }
            else
            {
                return 0;
            }
        }
    }
    return 1;
}
bool uu(int u,int v)
{
    if(lvl[u]>lvl[v])swap(u,v);
    for(int i=17;i>=0;i--)
    {
        if(lvl[v]-lvl[u]>=(1<<i))
        {
            if(U[i][v])
            {
                v=T[i][v];
            }
            else
            {
                return 0;
            }
        }
    }
    return 1;
}
void dfs(int nod,int tata,int nvl)
{
    lvl[nod]=nvl;
    for(auto it:G[nod])
    {
        if(it!=tata)
        {
            dfs(it,nod,nvl+1);
        }
    }
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>p>>t;
        P[i]=p;
        if(p==-1)continue;
        T[0][i]=p;
        G[i].push_back(p);
        G[p].push_back(i);
        if(t==0)SP[0][i]=1;
        else U[0][i]=1;
    }
    for(int k=1;k<=17;k++)
    {
        for(int i=1;i<=N;i++)
        {
            T[k][i]=T[k-1][T[k-1][i]];
            SP[k][i]=SP[k-1][i]&SP[k-1][T[k-1][i]];
            U[k][i]=U[k-1][i]&U[k-1][T[k-1][i]];
        }
    }
    for(int i=1;i<=N;i++)
    {
        if(P[i]==-1)dfs(i,0,1);
    }
    int Q;
    cin>>Q;
    while(Q--)
    {
        int t,u,v;
        cin>>t>>u>>v;
        if(t==1)
        {
            if(u==v)cout<<"NO";
            else if(lca(u,v)!=u){cout<<"NO";}
            else cout<<(sp(u,v) ? "YES":"NO");
        }
        else
        {
            int tmp=lca(u,v);
            if(tmp==v)cout<<"NO";
            else if(tmp==0)cout<<"NO";
            else cout<<(uu(v,tmp)&&sp(u,tmp) ? "YES":"NO");
        }
        cout<<"\n";
    }
    return 0;
}
