#include <iostream>
#include <vector>
using namespace std;
vector<int> G[55];
int N,M;
int rez;
bool viz[55];
int low[55];
void dfs(int nod,int tata,int lvl)
{
    viz[nod]=1;
    low[nod]=lvl;
    for(auto it:G[nod])
    {
        if(!viz[it])dfs(it,nod,lvl+1);
        if(it!=tata)low[nod]=min(low[nod],low[it]);
    }
    if(low[nod]==lvl)rez+=(tata!=0);
}
int main()
{
    cin>>N>>M;
    for(int i=1;i<=M;i++)
    {
        int x,y;
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(1,0,1);
    cout<<rez;
    return 0;
}
