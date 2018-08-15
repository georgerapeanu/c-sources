#include <cstdio>
using namespace std;
FILE *f=fopen("frunze.in","r");
FILE *g=fopen("frunze.out","w");
int D[51][51];
int i,j,N,P;
int main()
{
    fscanf(f,"%d %d",&N,&P);
    D[1][1]=1;
    for(i=2;i<=N;i++)
    {
        for(j=1;j<=P&&j<i;j++)
        {
            D[i][j]=D[i-1][j]*(j+i-2)+D[i-1][j-1]*(i-j);
        }

    }
    fprintf(g,"%d",D[N][P]);
    fclose(f);
    fclose(g);
    return 0;
}
