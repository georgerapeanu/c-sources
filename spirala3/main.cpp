#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("spirala3.in","r");
FILE *g=fopen("spirala3.out","w");
const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};
int N,M;
int V[55][55];
int dp[55][55][55][55][4];
int main()
{
    fscanf(f,"%d%d",&N,&M);
    for(int i=1;i<=N;i++)
    {
        mlin[i]=(1<<30);
        for(int j=1;j<=M;mcol[j]=(1<<30),j++)
            fscanf(f,"%d",&V[i][j]),dp[i][j][i][j][0]=dp[i][j][i][j][1]=dp[i][j][i][j][2]=dp[i][j][i][j][3]=1^V[i][j];
    }
    int rez=0;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            if(V[i][j]) continue;
            for(int x=1;x<=N-i+1;x++)
            {
                for(int y=1;y<=N-j+1;y++)
                {
                    if(V[i+x][j+y]) continue;
                    for(int dir=0;dir<=4;dir++)
                    {

                    }
                }
            }
        }
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
