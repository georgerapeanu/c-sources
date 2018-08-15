#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
vector<int> V[4];
struct{int x,y,z;long long sum=0;}dp[300005];
int W,C;
int N,M;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N>>M;
    for(int i=1;i<=N;i++)
    {
        cin>>W>>C;
        V[W].push_back(C);
    }
    sort(V[1].begin(),V[1].end());reverse(V[1].begin(),V[1].end());
    sort(V[2].begin(),V[2].end());reverse(V[2].begin(),V[2].end());
    sort(V[3].begin(),V[3].end());reverse(V[3].begin(),V[3].end());
    for(int i=1;i<=M;i++)
    {
        dp[i]=dp[i-1];
        if(i>=1&&dp[i-1].x<V[1].size()&&dp[i].sum<dp[i-1].sum+V[1][dp[i-1].x]){dp[i]=dp[i-1];dp[i].sum=dp[i-1].sum+V[1][dp[i-1].x];dp[i].x++;}
        if(i>=2&&dp[i-2].y<V[2].size()&&dp[i].sum<dp[i-2].sum+V[2][dp[i-2].y]){dp[i]=dp[i-2];dp[i].sum=dp[i-2].sum+V[2][dp[i-2].y];dp[i].y++;}
        if(i>=3&&dp[i-3].z<V[3].size()&&dp[i].sum<dp[i-3].sum+V[3][dp[i-3].z]){dp[i]=dp[i-3];dp[i].sum=dp[i-3].sum+V[3][dp[i-3].z];dp[i].z++;}
    }
    cout<<dp[M].sum;
    return 0;
}
