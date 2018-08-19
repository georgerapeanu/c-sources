#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
int C[6005];
int dp[6005][2];
bitset <6005> viz;
vector <int> G[6005];
int K,L;
int N;
void dfs(int nod)
{
    dp[nod][1]=C[nod];
    for(auto it:G[nod])
    {
        dfs(it);
        dp[nod][1]+=dp[it][0];
        dp[nod][0]+=max(dp[it][1],dp[it][0]);
    }
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
        cin>>C[i];
    cin>>K>>L;
    while(K!=0&&L!=0)
    {
        viz[K]=1;
        G[L].push_back(K);
        cin>>K>>L;
    }
    int i=1;
    while(viz[i])
        i++;
    dfs(i);
    cout<<max(dp[i][0],dp[i][1]);
    return 0;
}
