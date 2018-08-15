#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <bitset>
#define x first
#define y second
using namespace std;
FILE *f=fopen("tort3.in","r");
FILE *g=fopen("tort3.out","w");
int N,M;
char C[505][505];
int dp[505][505];
vector<pair<int,int> > V[505];
int main()
{
    fscanf(f,"%d %d\n",&N,&M);
    for(int i=1;i<=N;i++)
    {
        fgets(C[i]+1,505,f);
    }
    for(int i=N;i;i--)
    {
        for(int j=M;j;j--)
        {
            dp[i][j]=1+min(dp[i][j+1]*(C[i][j+1]==C[i][j]),min(dp[i+1][j]*(C[i+1][j]==C[i][j]),dp[i+1][j+1]*(C[i+1][j+1]==C[i][j])));
            V[dp[i][j]].push_back({i,j});
        }
    }
    for(int l=min(N,M);l;l--)
    {
        sort(V[l].begin(),V[l].end());
        for(auto it:V[l])
        {
            if(dp[it.x][it.y]==l)
            {
                fprintf(g,"%d %d %d\n",l,it.x+l-1,it.y+l-1);
                for(int i=it.x+l-1;i&&i>it.x-l;i--)
                {
                    for(int j=it.y+l-1;j&&j>it.y-l;j--)
                    {
                        if(it.x<=i&&i<it.x+l&&it.y<=j&&j<l+it.y)
                        {
                            dp[i][j]=0;
                            C[i][j]='-';
                        }
                        else if(C[i][j]!='-')
                        {
                            dp[i][j]=1+min(dp[i][j+1]*(C[i][j+1]==C[i][j]),min(dp[i+1][j]*(C[i+1][j]==C[i][j]),dp[i+1][j+1]*(C[i+1][j+1]==C[i][j])));
                            V[dp[i][j]].push_back({i,j});
                        }
                    }
                }
            }
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
