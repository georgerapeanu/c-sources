#include <iostream>
#include <algorithm>
#define MOD 1000000007
using namespace std;
int N;
pair<int,int> V[2005];
int dp[2005][2005];
int last[4005];
bool cmp(pair<int,int> a,pair<int,int> b)
{
    if(a.second!=b.second)return a.second<b.second;
    return a.first<b.first;
}
void mod(int &a)
{
    if(a>=MOD)a-=MOD;
    else if(a<0)a+=MOD;
}
int main() {
    cin>>N;
    for(int i=1;i<=N;i++)cin>>V[i].first>>V[i].second;
    sort(V+1,V+1+N,cmp);
    for(int i=1;i<=N;i++)last[V[i].second]=i;
    for(int i=1;i<=N;i++)last[i]=max(last[i],last[i-1]);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<i;j++)
        {
            if(V[i].first<=V[j].second)
            {
                dp[i][j]=1;
                mod(dp[i][j]+=dp[j][last[V[i].first-1]]);
                if(V[i].first<=V[j].first&&V[j].second<=V[i].second)
                    mod(dp[i][j]+=dp[i][last[V[j].first-1]]);
            }
            //cout<<dp[i][j]<<" ";
            mod(dp[i][j]+=dp[i][j-1]);
        }
        for(int j=i;j<=N;j++)dp[i][j]=dp[i][j-1];
        //cout<<"\n";
    }
    int rez=N;
    for(int i=1;i<=N;i++)mod(rez+=dp[i][N]);
    cout<<rez;
    return 0;
}
