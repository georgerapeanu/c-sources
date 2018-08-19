#include <iostream>
#include <set>
using namespace std;
bool viz[100005];
int V[100005];
set<int> S[100005];
int N,M;
void dfs(int nod,int &nr)
{
    viz[nod]=1;
    if(V[nr]!=nod)return ;
    nr++;
    while(S[nod].size())
    {
        if(S[nod].count(V[nr]))
        {
            S[nod].erase(V[nr]);
            S[V[nr]].erase(nod);
            dfs(V[nr],nr);
        }
        else
            break;
    }
}
int main() {
    cin>>N>>M;
    for(int i=1;i<=N;i++)cin>>V[i];
    for(int i=1;i<=M;i++)
    {
        int x,y;
        cin>>x>>y;
        S[x].insert(y);
        S[y].insert(x);
    }
    int tmp=1;
    dfs(1,tmp);
    cout<<(tmp>N);
    return 0;
}
