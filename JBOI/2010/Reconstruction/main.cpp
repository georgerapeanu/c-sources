#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<pair<int,pair<int,int> > > V;
int T[1030];
vector<int> G[1030];
int fi(int nod)
{
    if(T[nod]<0)return nod;
    else return T[nod]=fi(T[nod]);
}
void u(int fx,int fy)
{
    int x,y;
    x=fi(fx);
    y=fi(fy);
    if(x!=y)
    {
        G[fx].push_back(fy);
        G[fy].push_back(fx);
        if(T[x]<T[y]){T[x]+=T[y];T[y]=x;}
        else {T[y]+=T[x];T[x]=y;}
    }
}
int a,b,c;
int N;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        T[i]=-1;
        for(int j=i+1;j<=N;j++)
        {
            cin>>c;
            V.push_back({c,{i,j}});
        }
    }
    sort(V.begin(),V.end());
    for(auto it:V)
        u(it.second.first,it.second.second);
    for(int i=1;i<=N;i++)
    {
        sort(G[i].begin(),G[i].end());
        cout<<G[i].size()<<" ";
        for(auto it:G[i])cout<<it<<" ";
        cout<<"\n";
    }
    return 0;
}
