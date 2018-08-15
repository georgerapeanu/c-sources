#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *f=fopen("stiva.in","r");
FILE *g=fopen("stiva.out","w");
int dp[505][505];
char C[505];
int N;
int main()
{
    fgets(C+1,505,f);
    N=strlen(C+1);
    N-=(C[N]=='\n');
    for(int i=1;i<=N;i++)
        dp[i][i]=1;
    for(int d=1;d<N;d++)
    {
        for(int i=1;i<=N-d;i++)
        {
            dp[i][i+d]=dp[i][i+d-1]+1;
            for(int j=i;j<i+d;j++)
            {
                if(C[j]==C[i+d])
                {
                    dp[i][i+d]=min(dp[i][i+d],dp[i][j]+dp[j+1][i+d-1]);
                }
            }
        }
    }
    fprintf(g,"%d",2*dp[1][N]+N);
    fclose(f);
    fclose(g);
    return 0;
}
