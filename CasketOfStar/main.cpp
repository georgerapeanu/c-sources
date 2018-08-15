#include <iostream>
#include <vector>

using namespace std;
class CasketOfStar{
public:
    int maxEnergy(vector<int> weight)
    {
        int dp[55][55];
        int N=weight.size();
        for(int l=2;l<N;l++)
        {
            for(int i=0;i<N-l;i++)
            {
                dp[i][i+l]=0;
                for(int j=i+1;j<i+l;j++)
                {
                    dp[i][i+l]=max(dp[i][i+l],dp[i][j]+dp[j][i+l]+weight[i]*weight[i+l]);
                }
            }
        }
        return dp[0][N-1];
    }
};
int main()
{
    CasketOfStar a;
    cout<<a.maxEnergy({1,1,1,1,1,1,1,1,1,1,1,1,1,1,1});
    return 0;
}
