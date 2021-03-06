#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("zmax.in","r");
FILE *g=fopen("zmax.out","w");
int N,M,i,j,rez=-(1500*10000);
int S[505][505];
int D[505][505];
int C[505][505];
int A[505][505];
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            fscanf(f,"%d",&A[i][j]);
            S[i][j]=max(A[i][j-1]+A[i][j],A[i][j]+S[i][j-1]);
        }
        for(j=M;j>0;j--)
        {
            D[i][j]=max(A[i][j]+A[i][j+1],A[i][j]+D[i][j+1]);
        }
    }
  for (j=2;j<=M;j++) {
        C[N-1][j] = A[N-1][j] + D[N][j-1];
    }

    for (i=N-2;i>=1;i--) {
        C[i][2] = A[i][2] + D[i+1][1];
        for (j=3;j<=M;j++) {
            C[i][j] = max(C[i+1][j-1] + A[i][j], D[i+1][j-1] + A[i][j]);
        }
    }

    for(i=1;i<=N-2;i++)
    {
        for(j=3;j<=M;j++)
        {
            if(S[i][j]+C[i+1][j-1]>rez)
                rez=S[i][j]+C[i+1][j-1];
        }
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
