#include <iostream>
#include <cstdio>
#include <algorithm>
#define y first
#define x second
using namespace std;
long long dp[100005];
int N;
pair<int,int> V[100005];
int main()
{
    freopen("heavymetal.in","r",stdin);
    freopen("heavymetal.out","w",stdout);
    cin>>N;
    for(int i=1;i<=N;i++) cin>>V[i].x>>V[i].y;
    sort(V+1,V+1+N);
    for(int i=1;i<=N;i++)
    {
        int st=0,dr=i-1;
        while(st<dr)
        {
            int mid=(st+dr+1)/2;
            if(V[mid].y>V[i].x) dr=mid-1;
            else st=mid;
        }
        dp[i]=max(dp[st]+V[i].y-V[i].x,dp[i-1]);
    }
    cout<<dp[N];
    return 0;
}
