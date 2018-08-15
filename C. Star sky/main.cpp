#include <cstdio>
#include <vector>
using namespace std;
long long S[11][105][105];
vector<int> A[105][105];
int x,y,s;
int t,x1,y1,x2,y2;
int N,Q,c;
int main()
{
    scanf("%d %d %d",&N,&Q,&c);
    for(int i=1;i<=N;i++)
    {
        scanf("%d %d %d",&x,&y,&s);
        S[0][x][y]+=s;
        A[x][y].push_back(s);
    }
    for(int i=1;i<=100;i++)for(int j=1;j<=100;j++)S[0][i][j]=S[0][i][j]+S[0][i-1][j]+S[0][i][j-1]-S[0][i-1][j-1];
    for(int t=1;t<=c;t++)
    {
        for(int i=1;i<=100;i++)
        {
            for(int j=1;j<=100;j++)
            {
                for(int k=0;k<A[i][j].size();k++)
                {
                    A[i][j][k]++;if(A[i][j][k]>c)A[i][j][k]=0;
                    S[t][i][j]+=A[i][j][k];
                }
                S[t][i][j]=S[t][i][j]+S[t][i-1][j]+S[t][i][j-1]-S[t][i-1][j-1];
            }
        }
    }
    for(int i=1;i<=Q;i++)
    {
        scanf("%d %d %d %d %d",&t,&x1,&y1,&x2,&y2);
        printf("%I64d\n",S[t%(c+1)][x2][y2]-S[t%(c+1)][x2][y1-1]-S[t%(c+1)][x1-1][y2]+S[t%(c+1)][x1-1][y1-1]);
    }
    return 0;
}
