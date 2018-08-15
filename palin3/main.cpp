#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("palin3.in","r");
FILE *g=fopen("palin3.out","w");
int len,N;
int dp[205][205];
int T;
char C[205];
int main()
{
    fscanf(f,"%d\n",&T);
    for(int i=1;i<=T;i++)
    {
        fgets(C+1,205,f);
        N=strlen(C+1);
        N=N-(C[N]=='\n');
        for(int i=N;i;i--)
        {
            dp[i][i-1]=1;
            for(int j=i;j<=N;j++)
            {
                dp[i][j]=0;
                for(int k=i;k<=j;k++)
                    dp[i][j]=dp[i][j]|(dp[i][k]&dp[k+1][j]);
                if(C[i]==C[j])
                {
                    for(int k=i+1;k<j;k++)
                    {
                        dp[i][j]=dp[i][j]|(dp[i+1][k-1]&dp[k+1][j-1]);
                    }
                }
            }
        }
        fputs(dp[1][N] ? "DA\n":"NU\n",g);
    }
    fclose(f);
    fclose(g);
    return 0;
}
