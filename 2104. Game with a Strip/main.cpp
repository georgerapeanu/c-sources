#include <cstdio>
#define NMAX 1000001
using namespace std;
short dp[22][NMAX][2];
int S[NMAX];
char aux;
int N,p2,unit;
int main()
{
    scanf("%d\n",&N);
    for(int i=1;i<=N;i++)
    {
        scanf("%c",&aux);
        S[i]=S[i-1]+aux-'A';
    }
    scanf("\n");
    for(int i=N+1;i<=2*N;i++)
    {
        scanf("%c",&aux);
        S[i]=S[i-1]+aux-'A';
    }
    int cN=N;
    while(cN%2==0)
        cN/=2;
    for(int i=1;i<=2*N-cN+1;i++)
    {
        if(S[i+cN-1]-S[i-1]==0)
            dp[0][i][0]=dp[0][i][1]=0;
        else if(S[i+cN-1]-S[i-1]==cN)
            dp[0][i][0]=dp[0][i][1]=1;
        else
            dp[0][i][0]=dp[0][i][1]=-1;
    }
    unit=cN;
    cN=N/cN;
    while(cN)
    {
        p2++;
        cN/=2;
    }
    for(int j=1;j<=p2;j++)
    {
        for(int i=2*N-unit*(1<<j)+1;i;i--)
        {
            if(j!=1)
            {
                if(dp[j-1][i][1]==0||dp[j-1][i+unit*(1<<(j-1))][1]==0)
                    dp[j][i][0]=0;
                else if(dp[j-1][i][1]==1&&dp[j-1][i+unit*(1<<(j-1))][1]==1)
                    dp[j][i][0]=1;
                else
                    dp[j][i][0]=-1;
                if(dp[j-1][i][0]==1||dp[j-1][i+unit*(1<<(j-1))][0]==1)
                    dp[j][i][1]=1;
                else if(dp[j-1][i][0]==0&&dp[j-1][i+unit*(1<<(j-1))][0]==0)
                    dp[j][i][1]=0;
                else
                    dp[j][i][1]=-1;
            }
            else
            {
                if(dp[j-1][i][1]==0&&dp[j-1][i+unit*(1<<(j-1))][1]==0)
                    dp[j][i][1]=dp[j][i][0]=0;
                else if(dp[j-1][i][1]==1&&dp[j-1][i+unit*(1<<(j-1))][1]==1)
                    dp[j][i][1]=dp[j][i][0]=1;
                else
                    dp[j][i][1]=dp[j][i][0]=-1;
            }
        }
    }
    if(dp[p2][1][0]==1)
        printf("Bob");
    else if(dp[p2][1][0]==0)
        printf("Alice");
    else
        printf("Draw");
    return 0;
}
