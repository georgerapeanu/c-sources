#include <iostream>
#include <algorithm>
using namespace std;
int N;
pair<int,int> V[200005];
int X[100005];
int Y[100005];
int dp[100005][2][2];
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i].first>>V[i].second;
    }
    sort(V+1,V+1+N);
    for(int i=1;i<=2*N;i++)
    {
        if(X[V[i].first]==0){dp[i][1][0]++;dp[i][1][1]++;}
        else {dp[i][1][0]+=}
    }
    return 0;
}
