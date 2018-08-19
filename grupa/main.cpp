#include <cstdio>
using namespace std;
FILE *f=fopen("grupa.in","r"),*g=fopen("grupa.out","w");
int N,C[100][100],i,j;
int main()
{
    fscanf(f,"%d",&N);
    for(i=0;i<=N;i++)
        C[i][i]=C[i][0]=1;
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=i;j++)
        C[i][j]=C[i-1][j-1]+C[i-1][j];
    }
    for(i=1; )
    return 0;
}
