#include <iostream>
#include <cstring>
#include <map>
using namespace std;
map<int,int> linnum[5005],colnum[5005];
int linmod[5005][7],colmod[5005][7];
int dp[5005][5005];
int V[5005];
int N;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)cin>>V[i];
    int rez=0;
    for(int i=N;i;i--)
    {
        for(int j=N;j;j--)
        {
            if(i==j)continue;
        }
        for(int j=N;j;j--)
        {

        }
    }
    for(int i=1;i<=N;i++){for(int j=1;j<=N;j++)cerr<<dp[i][j]<<" ";cerr<<"\n";}
    ///cout<<rez;
    return 0;
}
