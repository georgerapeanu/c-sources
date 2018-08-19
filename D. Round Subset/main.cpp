#include <iostream>
#define LOG 25
#define NMAX 200
using namespace std;
int dp[2][NMAX+5][NMAX*LOG+5];
int N,K;
int lg2,lg5;
int rez;
int kmax;
int main()
{
    for(int k=0;k<=NMAX;k++)for(int j=0;j<=NMAX*LOG;j++)dp[0][k][j]=-(1<<30);
    dp[0][0][0]=0;
    cin>>N>>K;
    for(int i=1;i<=N;i++)
    {
        for(int k=0;k<=NMAX;k++)for(int j=0;j<=NMAX*LOG;j++)dp[i%2][k][j]=-(1<<30);
        long long val;
        cin>>val;
        lg2=lg5=0;
        while(val%2==0){lg2++;val/=2;}
        while(val%5==0){lg5++;val/=5;}
        for(int j=0;j<=i&&j<=K;j++)
        {
            for(int k=0;k<=kmax+lg5;k++)
            {
                dp[i%2][j][k]=dp[1-i%2][j][k];
                if(j&&k>=lg5)dp[i%2][j][k]=max(dp[i%2][j][k],dp[1-i%2][j-1][k-lg5]+lg2);
            }
        }
        kmax+=lg5;
    }
    for(int j=0;j<=kmax;j++)rez=max(rez,min(j,dp[N%2][K][j]));
    cout<<rez;
    return 0;
}
