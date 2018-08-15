#include <iostream>

using namespace std;
class NoRepeatPlaylist{
public:
    int numPlaylists(int N,int M,int P)
    {
        const long long MOD=1000000007;
        long long dp[105][105];
        for(int i=0;i<=P;i++)
            for(int j=0;j<=N;j++)
                dp[i][j]=0;
        dp[M][M]=1;
        for(int i=N;i>N-M;i--)
            dp[M][M]=(dp[M][M]*i)%MOD;
        for(int i=M+1;i<=P;i++)
        {
            int tmp=min(i,N);
            for(int j=1;j<=tmp;j++)
            {
                dp[i][j]=((N-j+1)*dp[i-1][j-1]+dp[i-1][j]*(j-M))%MOD;
            }
        }
        return dp[P][N];
    }
};
int main()
{
    NoRepeatPlaylist a;
    cout<<a.numPlaylists(2,0,4);
    return 0;
}
