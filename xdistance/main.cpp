#include <iostream>
#include <vector>
#include <algorithm>
#define cost first
#define n1 second.first
#define n2 second.second
using namespace std;
int N,M,X,a;
long long rez;
typedef pair<int,pair<int,int> > muchie;
vector<muchie> G;
int T[100005],u,v;
int fi(int x)
{
    if(T[x]<0)return x;
    T[x]=fi(T[x]);
    return T[x];
}
void un(int x,int y)
{
    x=fi(x);
    y=fi(y);
    if(x==y) return;
    T[y]+=T[x];
    T[x]=y;
}
int main() {
    cin>>N>>M>>X;
    for(int i=1;i<=N;i++)T[i]=-1;
    for(int i=1;i<=M;i++)
    {
        cin>>u>>v>>a;
        G.push_back({a,{u,v}});
    }
    sort(G.begin(),G.end());
    for(int i=0;i<G.size();i++)
    {
        if(G[i].cost>X)break;
        else
        {
            if(G[i].cost==X)
            {
                if(fi(G[i].n1)!=fi(G[i].n2))
                {
                    rez+=T[fi(G[i].n1)]*T[fi(G[i].n2)];
                }
            }
            un(G[i].n1,G[i].n2);
        }
    }
    cout<<rez;
    return 0;
}
