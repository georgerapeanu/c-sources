#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
FILE *f=fopen("gard3.in","r");
FILE *g=fopen("gard3.out","w");
typedef int tp;
const int LEN=100;
const tp BASE=10000;
int N,K;
tp dp[51][51][LEN];
void init(tp A[],int val)
{
    memset(A,0,sizeof(tp)*(A[0]+1));
    while(val){A[++A[0]]=val%BASE;val/=BASE;}
    A[0]=max(1,A[0]);
}
void add(tp A[],tp B[])
{
    tp t=0;
    for(int i=1;i<=A[0]||i<=B[0]||t;i++)
    {
        A[i]=A[i]+B[i]+t;
        t=A[i]/BASE;
        A[i]%=BASE;
        A[0]=max(A[0],i);
    }
}
tp C[LEN];
tp tmp[LEN];
void mult(tp A[],tp B[])
{
    init(C,0);
    C[0]=A[0]+B[0]-1;
    for(int i=1;i<=A[0];i++)
        for(int j=1;j<=B[0];j++)
            C[i+j-1]+=A[i]*B[j];
    tp t=0;
    for(int i=1;i<=C[0]||t;i++)
    {
        C[i]+=t;
        t=C[i]/BASE;
        C[i]%=BASE;
        C[0]=max(C[0],i);
    }
    memcpy(A,C,sizeof(C));
}
void afis(tp A[])
{
    fprintf(g,"%d",A[A[0]]);
    for(int i=A[0]-1;i;i--)
    {
        int cb=BASE/10;
        while(cb>A[i]&&cb>1)
        {
            fprintf(g,"0");
            cb/=10;
        }
        fprintf(g,"%d",A[i]);
    }
}
int DP[105][105][3];
int main()
{
    fscanf(f,"%d%d",&N,&K);K--;
    for(int i=0;i<=N;i++)DP[i][0][0]=DP[i][0][1]=DP[i][0][2]=1;

    for(int i=4;i<=N;i++)
    {
        for(int j=1;j<=K;j++)
        {
            DP[i][j][0]=DP[i-1][j][2]+DP[i-1][j-1][0];
            for(int k=3;k<i;k++)
            {
                for(int l=0;l<j;l++)
                {
                    DP[i][j][1]+=DP[k][l][2]*DP[i-k+1][j-1-l][2];
                }
            }
            DP[i][j][2]=DP[i][j][0]+DP[i][j][1];
            //printf("%d ",DP[i][j]);
        }
        //printf("\n");
    }
    fprintf(g,"%d",DP[N][K][2]);
    return 0;
}
