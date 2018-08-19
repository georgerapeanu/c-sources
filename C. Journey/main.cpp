#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
vector<int> G[100005];
long double ans;
int N;
void dfs(int nod,int tata,long double p,int lvl)
{
    if(G[nod].size()==1&&nod!=1){ans+=p*lvl;return ;}
    for(auto it:G[nod])if(it!=tata)dfs(it,nod,p/(G[nod].size()-(nod!=1)),lvl+1);
}
int main()
{
    cin>>N;
    for(int i=1;i<N;i++)
    {
        int x,y;
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(1,0,1,0);
    cout<<fixed<<setprecision(10)<<ans;
    return 0;
}
