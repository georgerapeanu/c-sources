#include <cstdio>
#include <cstring>
#include <algorithm>
#define inf 4000000000000
using namespace std;
FILE *f=fopen("similar.in","r");
FILE *g=fopen("similar.out","w");
char A[2005],B[2005];
long long N,M,i,j,m[2005][2005],a[2005],b[2005];
int main()
{
    A[0]=B[0]='.';
    fgets(A+1,2005,f);
    fgets(B+1,2005,f);
    N=strlen(A)-2;
    M=strlen(B)-2;
    for(i=1;i<=N;i++)
        fscanf(f,"%lld",&a[i]);
    for(i=1;i<=N;i++)
        fscanf(f,"%lld",&b[i]);
    for(i=1;i<=N;i++)
        m[i][0]=m[i-1][0]+a[i];
    for(i=1;i<M;i++)
        m[0][i]=inf;
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            if(i<j)
            m[i][j]=inf;
            else
                m[i][j]=min(m[i-1][j-1]+(A[i]!=B[j])*b[i],m[i-1][j]+a[i]);
        }
    }
    fprintf(g,"%lld",m[N][M]);
    fclose(f);
    fclose(g);
    return 0;
}
