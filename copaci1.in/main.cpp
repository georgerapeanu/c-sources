#include <cstdio>
using namespace std;
FILE *f=fopen("copaci1.in","r");
FILE *g=fopen("copaci1.out","w");
int N,M;
int A[110][110],i,j,minim,B[110][110];
bool pos=1,full;
int main()
{
    fscanf(f,"%d%d",&N,&M);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
            fscanf(f,"%d",&A[i][j]);
    }
    while(pos&&!full)
    {
        pos=0;full=1;
        for(i=1;i<=N;i++)
        {
            for(j=1;j<=M;j++)
                if(A[i][j]==0)
                    if(A[i-1][j]+A[i][j-1]+A[i+1][j]+A[i][j+1]>=2)
                    {
                        pos=1;full=0;B[i][j]=1;
                    }
        }
        for(i=1;i<=N;i++)
        {
            for(j=1;j<=M;j++)
            {
                A[i][j]=A[i][j]||B[i][j];
                B[i][j]=0;
            }
        }
        minim++;
    }
    if(full==1)
        fprintf(g,"%d",minim-1);
    else
        fprintf(g,"IMPOSIBIL\n%d",minim-1);
    fclose(f);
    fclose(g);
    return 0;
}
