#include <cstdio>
using namespace std;
FILE *f=fopen("dezastru.in","r");
FILE *g=fopen("dezastru.out","w");
int N,K,i,j;
double sol[30][30],comb[30][30],V[30];
int main()
{
    fscanf(f,"%d %d",&N,&K);
    for(i=1;i<=N;i++)
        fscanf(f,"%lf",&V[i]);
    for(i=0;i<=N;i++)
        comb[i][0]=comb[i][i]=sol[i][0]=1;
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=K;j++)
        {
            comb[i][j]=comb[i-1][j]+comb[i-1][j-1];
            sol[i][j]=sol[i-1][j]+sol[i-1][j-1]*V[i];
        }
    }
    fprintf(g,"%lf",sol[N][K]/comb[N][K]);
    fclose(f);
    fclose(g);
    return 0;
}
