#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
int weight[1005];
int X[1005];
int N;
int P[1005];
vector<int> G[1005];
bool dp[1005][5005];
void dfs(int nod)
{
    long long ceva=0;
    for(auto it:G[nod])
    {
            dfs(it);
            weight[nod]+=weight[it];
            ceva+=min(X[it],weight[it]-X[it]);
    }
    if(X[nod]<ceva)
    {
        cout<<"IMPOSSIBLE";
        exit(0);
    }
    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    for(int i=0;i<G[nod].size();i++)
    {
        int it=G[nod][i];
        for(int j=0;j<=X[nod];j++)
        {
            if(dp[i][j])
            {
                if(j+X[it]<=X[nod])dp[i+1][j+X[it]]=1;
                if(j+weight[it]-X[it]<=X[nod])dp[i+1][j+weight[it]-X[it]]=1;
            }
        }
    }
    int tmp=X[nod];
    while(tmp>0&&!dp[G[nod].size()][tmp])tmp--;
    weight[nod]+=X[nod]-tmp;
}
int main()
{
    cin>>N;
    for(int i=2;i<=N;i++)
    {
        cin>>P[i];
        G[P[i]].push_back(i);
    }
    for(int i=1;i<=N;i++)cin>>X[i];
    dfs(1);
    cout<<"POSSIBLE";
    return 0;
}
