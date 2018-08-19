#include <iostream>
#include <vector>
#define inf 1LL<<62
using namespace std;
long long dp[501][501][3];
struct{int x,y,z;} p[501][501][3],poz;
long long val[501][501];
vector <int> rez;
int N,M;
int main()
{
    cin>>N>>M;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            cin>>val[i][j];
    for(int i=1;i<=M;i++)
    {
        dp[1][i][2]=val[1][i];
        dp[1][i][1]=inf;
        dp[1][i][0]=inf;
    }
    for(int i=2;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            dp[i][j][0]=dp[i][j][1]=dp[i][j][2]=inf;
            if(dp[i-1][j][0]<dp[i-1][j][1]&&dp[i-1][j][0]<dp[i-1][j][2])
            {
                p[i][j][2]={i-1,j,0};
                dp[i][j][2]=dp[i-1][j][0]+val[i][j];
            }
            else if(dp[i-1][j][1]<dp[i-1][j][2]&&dp[i-1][j][1]<dp[i-1][j][0])
            {
                p[i][j][2]={i-1,j,1};
                dp[i][j][2]=dp[i-1][j][1]+val[i][j];
            }
            else
            {
                p[i][j][2]={i-1,j,2};
                dp[i][j][2]=dp[i-1][j][2]+val[i][j];
            }
            if(j!=1)
            {
                if(dp[i][j-1][0]<dp[i][j-1][2])
                {
                    p[i][j][0]={i,j-1,0};
                    dp[i][j][0]=dp[i][j-1][0]+val[i][j];
                }
                else
                {
                    p[i][j][0]={i,j-1,2};
                    dp[i][j][0]=dp[i][j-1][2]+val[i][j];
                }
            }
        }
        for(int j=M;j>=1;j--)
            if(j!=M)
            {
                if(dp[i][j+1][1]<dp[i][j+1][2])
                {
                    p[i][j][1]={i,j+1,1};
                    dp[i][j][1]=dp[i][j+1][1]+val[i][j];
                }
                else
                {
                    p[i][j][1]={i,j+1,2};
                    dp[i][j][1]=dp[i][j+1][2]+val[i][j];
                }
            }
    }
    poz={N,1,0};
    for(int i=1;i<=M;i++)
    {
        if(dp[N][i][0]<dp[poz.x][poz.y][poz.z])
            poz={N,i,0};
        if(dp[N][i][1]<dp[poz.x][poz.y][poz.z])
            poz={N,i,1};
        if(dp[N][i][2]<dp[poz.x][poz.y][poz.z])
            poz={N,i,2};
    }
    while(poz.x)
    {
        rez.push_back(poz.y);
        poz=p[poz.x][poz.y][poz.z];
    }
    for(vector<int>::reverse_iterator it=rez.rbegin();it!=rez.rend();it++)
        cout<<*it<<" ";
    return 0;
}
