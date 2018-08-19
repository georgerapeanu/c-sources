#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#define NMAX 1000005
#define CMAX 10005
using namespace std;
char C[NMAX];
int N;
int nrcuv,lung;
int dp[CMAX][2];
int main()
{
    ///freopen("1.in","r",stdin);
    while(fgets(C+1,NMAX,stdin)!=NULL)
    {
        N=strlen(C+1);
        int i=1;
        while(i<=N)
        {
            while(i<=N&&!isalpha(C[i]))
                i++;
            if(i>N)
                break;
            nrcuv++;lung=0;
            while(i<=N&&isalpha(C[i]))
            {
                lung++;
                i++;
            }
            dp[nrcuv][0]=max(dp[nrcuv-1][1],dp[nrcuv-1][0]);
            dp[nrcuv][1]=dp[nrcuv-1][0]+lung;
        }
    }
    printf("%d",max(dp[nrcuv][0],dp[nrcuv][1]));
    return 0;
}
