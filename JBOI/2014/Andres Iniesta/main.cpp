#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int N,M,K;
char A[205][205];
int rez;
int U[205][205][55];
int L[205][205][55];
int D[205][205][55];
int R[205][205][55];
int Ux,Uy;
int Lx,Ly;
int Dx,Dy;
int Rx,Ry;
int dp[55];
int main()
{
    scanf("%d %d %d\n",&N,&M,&K);
    for(int i=1;i<=N;i++)
    {
        fgets(A[i]+1,205,stdin);
        A[i][0]=A[i][M+1]='*';
    }
    for(int i=0;i<=M+1;i++)
        A[0][i]=A[N+1][i]='*';

    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            if(A[i][j]!='*')
            {
                for(int k=0;k<=K;k++)
                    U[i][j][k]=U[i-1][j][k]+1;
                for(int k=0;k<=K;k++)
                    L[i][j][k]=L[i][j-1][k]+1;
            }
            else
            {
                for(int k=1;k<=K;k++)
                    U[i][j][k]=U[i-1][j][k-1]+1;
                for(int k=1;k<=K;k++)
                    L[i][j][k]=L[i][j-1][k-1]+1;
            }
        }
    }
    for(int i=N;i;i--)
    {
        for(int j=M;j;j--)
        {
            if(A[i][j]!='*')
            {
                for(int k=0;k<=K;k++)
                    D[i][j][k]=D[i+1][j][k]+1;
                for(int k=0;k<=K;k++)
                    R[i][j][k]=R[i][j+1][k]+1;
            }
            else
            {
                for(int k=1;k<=K;k++)
                    D[i][j][k]=D[i+1][j][k-1]+1;
                for(int k=1;k<=K;k++)
                    R[i][j][k]=R[i][j+1][k-1]+1;
            }
        }
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            int ck=K-(A[i][j]=='*');
            int nr=0;
            memset(dp,0,sizeof(dp));
            for(int k=K;k>=0;k--)
                for(int l=0;l<=k;l++)
                    dp[k]=max(dp[k],dp[k-l]+U[i-1][j][l]);
            for(int k=K;k>=0;k--)
                for(int l=0;l<=k;l++)
                    dp[k]=max(dp[k],dp[k-l]+R[i][j+1][l]);
            for(int k=K;k>=0;k--)
                for(int l=0;l<=k;l++)
                    dp[k]=max(dp[k],dp[k-l]+D[i+1][j][l]);
            for(int k=K;k>=0;k--)
                for(int l=0;l<=k;l++)
                    dp[k]=max(dp[k],dp[k-l]+L[i][j-1][l]);
            for(int i=0;i<=ck;i++)
                nr=max(nr,1+dp[i]);
            if(rez<nr)
            {
                rez=nr;
            }
        }
    }
    printf("%d",rez);
    return 0;
}
