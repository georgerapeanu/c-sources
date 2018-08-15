#include <cstdio>
using namespace std;
FILE *f=fopen("jetoane.in","r");
FILE *g=fopen("jetoane.out","w");
long long dp[15][15];
int i,j,a,S;
int main()
{
    fscanf(f,"%d\n%d",&S,&a);
    for(i=1;i<=a;i++)
        dp[i][0]=1;
    for(i=1;i<=a;i++)
    {
        for(j=1;j<=S;j++)
        {
            dp[i][j]=dp[i][j-1]+dp[i-1][j];
        }
    }
    fprintf(g,"%lld",dp[a][S]);
    return 0;
}
///incearca intrare cu spatiu in loc de linie noua;
