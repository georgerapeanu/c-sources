#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
int dp[100005],N;
int sz[100005];
vector<int> G[100005];
bitset<100005> U;
void dfs(int nod,int tata)
{
    sz[nod]=1;
    for(auto it:G[nod])
    {
        if(it==tata)continue;
        dfs(it,nod);
    }
    U.reset();
    for(auto it:G[nod])
    {
        if(it==tata)continue;
        sz[nod]+=sz[it];
        U[dp[it]]=1;
    }
    U[sz[nod]]=1;
    while(U[dp[nod]])++dp[nod];
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
    dfs(1,0);
    int rez=0;
    for(auto it:G[1])
    {
        rez^=dp[it];
    }
    if(rez!=0)cout<<"Alice";
    else cout<<"Bob";
    return 0;
}
