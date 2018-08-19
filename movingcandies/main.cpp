#include<vector>
#include <iostream>
#include <string>
#define inf (1<<30)
using namespace std;
class MovingCandies
{
	public:
	int minMoved(vector<string> a)
	{
		int dx[]={-1,0,1,0};
		int dy[]={0,1,0,-1};
		int dp[21][21][401];
		int N,M,nrcandys=0;
		N=a.size();
		M=a[0].size();
		for(int i=0;i<N;i++)
			for(int j=0;j<M;j++)
            {
                nrcandys+=(a[i][j]=='#');
                dp[i][j][1]=inf;
            }
		dp[0][0][1]=(a[0][0]!='#');
		for(int l=2;l<=nrcandys;l++)
		{
			for(int i=0;i<N;i++)
			{
				for(int j=0;j<M;j++)
				{
					dp[i][j][l]=inf;
					for(int k=0;k<4;k++)
						if(i+dx[k]>=0&&i+dx[k]<N&&j+dy[k]>=0&&j+dy[k]<M)
							dp[i][j][l]=min(dp[i+dx[k]][j+dy[k]][l-1]+(a[i][j]!='#'),dp[i][j][l]);
				}
			}
		}
		int minim=inf;
		for(int i=1;i<=nrcandys;i++) minim=min(minim,dp[N-1][M-1][i]);
		if(minim==inf) return -1;
		return minim;
	}
};
int main()
{
    MovingCandies a;
    cout<<a.minMoved({"#...###","#...#.#","##..#.#",".#....#"});
    return 0;
}
