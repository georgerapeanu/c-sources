#include <iostream>
#include <cstring>
#include <vector>
#define MOD 1000000007
using namespace std;
int dp[100005][12][3];///0-nu e boss,1-e boss,2- nu e dar e tatal
int dp2[100005][12][4];///0-nu e boss,pana la M-1,1-nu e boss,pana la K-1,2-e boss
vector<int> G[100005];
int N,X,K,M;
int add(int a,int b)
{
    a+=b;
    if(a>=MOD)a-=MOD;
    return a;
}
int mult(int a,int b)
{
    return 1LL*a*b%MOD;
}
void dfs(int nod,int tata)
{
    for(auto it:G[nod])if(it!=tata)dfs(it,nod);
    memset(dp2,0,sizeof(dp2));
    dp2[0][0][0]=dp2[0][0][1]=dp2[0][0][2]=1;
    for(int i=1;i<=G[nod].size();i++)
    {
        int it=G[nod][i-1];
        if(it==tata)continue;
        for(int j=0;j<=X;j++)
        {
            for(int k=0;k<=j;k++)
            {
                dp2[i][j][0]=dp2[i][j][0]+dp[it][k][0]*dp2[i-1][j-k][0];
                dp2[i][j][1]=dp2[i][j][1]+(dp[it][k][1]+dp[it][k][0])*dp2[i-1][j-k][1];
                dp2[i][j][2]=dp2[i][j][2]+dp[it][k][2]*dp2[i-1][j-k][2];
            }
        }
    }
    for(int i=0;i<=X;i++)
    {
        dp[nod][i][0]=dp2[G]
    }
}
int main()
{
    cin>>N>>M;
    for(int i=1;i<N;i++)
    {
        int x,y;
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    cin>>K>>X;
    dfs(1,0);
    cout<<add(mult(dp[1][X][0],M-1),dp[1][X][1]);
//    for(int i=1;i<=N;i++)
//    {
//        for(int j=0;)
//    }
    return 0;
}
