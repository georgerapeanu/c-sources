#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
FILE *f=fopen("agitatie.in","r");
FILE *g=fopen("agitatie.out","w");
int N;
int A[3005];
int S[3005];
int dp[2][6005];
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++) fscanf(f,"%d %d",&A[i],&S[i]);
    for(int i=1;i<=N;i++)
    {
        dp[i%2][0]=dp[1-i%2][0]+A[i];
        int minim=dp[1-i%2][0];
        for(int j=1;j<=6000;j++)
        {
            minim=min(minim,dp[1-i%2][j]);
            dp[i%2][j]=minim+abs(A[i]+j*S[i]);
        }
    }
    int minim=(1<<30);
    for(int i=1;i<=6000;i++)
        minim=min(minim,dp[N%2][i]);
    fprintf(g,"%d",minim);
    fclose(f);
    fclose(g);
    return 0;
}
