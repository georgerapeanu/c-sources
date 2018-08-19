#include <iostream>
#include <vector>
using namespace std;
int dp[2][100005];
int pecare[100005];
vector<int> G[100005];
void dfs(int nod,int tata)
{
    int nr=(1<<30);pecare[nod]=0;
    for(auto it:G[nod]) if(it!=tata) dfs(it,nod);
    for(auto it:G[nod])
    {
        if(it==tata) continue;
        if(dp[0][it]>dp[1][it])dp[0][nod]+=dp[0][it];
        else dp[0][nod]+=dp[1][it];
        if(dp[1][it]-dp[0][it]<nr){nr=dp[1][it]-dp[0][it];pecare[nod]=it;}
    }
    if(pecare[nod]==0) return;
    dp[1][nod]++;
    for(auto it:G[nod])
    {
        if(it==tata) continue;
        if(pecare[nod]==it)dp[1][nod]+=dp[0][it];
        else if(dp[0][it]>dp[1][it])dp[1][nod]+=dp[0][it];
        else dp[1][nod]+=dp[1][it];
    }
}
int N,M,x,y;
void recon(int tip,int nod,int tata)
{
    if(tip==1)
    {
        if(!pecare[nod]) return;
        cout<<nod<<" "<<pecare[nod]<<"\n";
    }
    for(auto it:G[nod])
    {
        if(tata==it) continue;
        else if(tip==1&&pecare[nod]==it)recon(0,it,nod);
        else
        {
            if(dp[0][it]>dp[1][it]) recon(0,it,nod);
            else recon(1,it,nod);
        }
    }
}
int main()
{
    cin>>N>>M;
    for(int i=1;i<=M;i++)
    {
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(1,0);
    cout<<max(dp[0][1],dp[1][1])<<"\n";
    if(dp[0][1]>dp[1][1])
    {
        recon(0,1,0);
    }
    else
    {
        recon(1,1,0);
    }
    return 0;
}
