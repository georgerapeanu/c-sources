#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
FILE *f=fopen("edist.in","r");
FILE *g=fopen("edist.out","w");
int dp[2][20005];
int N;
int M;
int K;
char A[20005];
char B[20005];
int main()
{
    fscanf(f,"%d %d %d\n",&N,&M,&K);
    fgets(A+1,20005,f);
    fgets(B+1,20005,f);
    for(int i=1;i<=M;i++)
        dp[0][i]=i;
    int l=1;
//    for(int j=0;j<=M;j++)printf("%d ",dp[0][j]);printf("\n");
    for(int i=1;i<=N;i++,l^=1)
    {
        dp[l][0]=i;
        int st=max(1,i-K);
        int dr=min(M,i+K);
        for(int j=st;j<=dr;j++)
        {
            int a,b,c;
            if(dp[1-l][j]!=0||(dp[1-l][j]==0&&i-1==j))a=dp[1-l][j]+1;
            else a=K+20;
            if(dp[l][j-1]!=0||(dp[l][j-1]==0&&i==j-1))b=dp[l][j-1]+1;
            else b=K+20;
            if(dp[1-l][j-1]!=0||(dp[1-l][j-1]==0&&i-1==j-1))c=dp[1-l][j-1];
            else c=K+20;
            dp[l][j]=min(min(a,b),c+(A[i]!=B[j]));
        }
//        for(int j=0;j<=M;j++)printf("%d ",dp[l][j]);printf("\n");
    }
    fprintf(g,"%d",dp[1-l][M]);
    fclose(f);
    fclose(g);
    return 0;
}
