#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("cmlsc.in","r");
FILE *g=fopen("cmlsc.out","w");
int N,M,i,j,m[2000][2000],A[2000],B[2000],rez[2000],nr;
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N;i++)
        fscanf(f,"%d",&A[i]);
    for(i=1;i<=M;i++)
        fscanf(f,"%d",&B[i]);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            if(A[i]==B[j]) m[i][j]=m[i-1][j-1]+1;
            else           m[i][j]=max(m[i-1][j],m[i][j-1]);
        }
    }
    i=N;
    j=M;
    while(j&&i)
    {
        if(A[i]==B[j])
        {
            rez[++nr]=A[i];
            i--;
            j--;
        }
        else if(m[i-1][j]>m[i][j-1])
            i--;
        else
            j--;
    }
    fprintf(g,"%d\n",nr);
    for(i=nr;i>=1;i--)
        fprintf(g,"%d ",rez[i]);
    return 0;
}
