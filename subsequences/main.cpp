#include <iostream>
using namespace std;
int n,k,i,v[100010],j,nr,dp[100010][11],p,sum;
int main()
{
    cin>>n>>k;
    for(i=1;i<=n;i++)
    {cin>>v[i];dp[i][1]=1;}
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=k+1;j++)
        {
            for(p=1;p<i;p++)
            {
                if(v[p]<v[i])
                {
                    dp[i][j]+=dp[p][j-1];
                }
            }
        }
    }
    for(i=1;i<=n;i++)
    {
        sum+=dp[i][k+1];
    }
    cout<<sum;
    return 0;
}
