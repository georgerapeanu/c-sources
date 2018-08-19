#include <iostream>
#define LEN 300
using namespace std;
int dp[100005][LEN+5];
int A[100005];
int N,Q,P;
int K;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>A[i];
    }
    for(int i=N;i;i--)
    {
        for(int j=1;j<=LEN;j++)
        {
            dp[i][j]=(i+j+A[i]>N ? 0:dp[i+j+A[i]][j])+1;
        }
    }
    cin>>Q;
    while(Q--)
    {
        cin>>P>>K;
        if(K<=LEN)
        {
            cout<<dp[P][K];
        }
        else
        {
            int nr=0;
            for(int i=P;i<=N;i+=K+A[i])
                nr++;
            cout<<nr;
        }
        cout<<"\n";
    }
    return 0;
}
