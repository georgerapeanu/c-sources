#include <iostream>

using namespace std;
int N;
int V[2005];
int dp[2005][5000];
int cost(int a,int b)
{
    int nra=0,nrb=0;
    for(int i=0;i<12;i++)
    {
        if(((a>>i)&1)&&((b>>i)&1));
        else if(!((a>>i)&1)&&!((b>>i)&1));
        else if(((a>>i)&1))nra++;
        else if(((b>>i)&1))nrb++;
    }
    return (nra!=nrb ? 1<<20:nra);
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i];
        for(int j=0;j<4096;j++)
        {
            if(j)dp[i][j]=dp[i][j-1];
            else dp[i][j]=1<<20;
            dp[i][j]=min(dp[i][j],dp[i-1][j]+cost(V[i],j));
        }
    }
    cout<<dp[N][4095];
    return 0;
}
