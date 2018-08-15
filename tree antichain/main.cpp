#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int T,N;
vector<int> G[10005];
int nvl[10005];
int mlvl;
vector<pair<int,int> >V;
bool dfs(int nod,int lvl,int tata)
{
    V.push_back({lvl,nod});
    mlvl=max(mlvl,lvl);
    nvl[nod]=lvl;
    for(auto it:G[nod])if(it!=tata)dfs(it,lvl+1,nod);
}
int main() {
    cin>>T;
    while(T--)
    {
        cin>>N;
        for(int i=1;i<N;i++)
        {
            int x,y;
            cin>>x>>y;
            G[x].push_back(y);
            G[y].push_back(x);
        }
        mlvl=0;
        dfs(1,1,0);int nod=V.back().second;V.clear();
        dfs(nod,1,0);
        if(mlvl<=3)
        {
            cout<<-1<<"\n";
        }
        else
        {
            sort(V.begin(),V.end());
            if(N%2==1)for(auto it:V)if(it.first%2==1)cout<<it.second<<" ";
            for(auto it:V)if(it.first%2==0)cout<<it.second<<" ";
            if(N%2==0)for(auto it:V)if(it.first%2==1)cout<<it.second<<" ";
            cout<<"\n";
        }
        for(int i=1;i<=N;i++){G[i].clear();nvl[i]=0;}V.clear();
    }
    return 0;
}
