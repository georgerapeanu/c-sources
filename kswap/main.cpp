#include <cstdio>
using namespace std;
FILE *f=fopen("kswap.in","r");
FILE *g=fopen("kswap.out","w");
int N,K,i,j;
int V[155][11200];
int main()
{
    fscanf(f,"%d %d",&N,&K);
    for(i=0;i<=N;i++)
    {
        V[i][0]=1;
    }
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=(i-1)*i/2;j++)
        {
            if(j>=i)
                V[i][j]=(V[i][j-1]+V[i-1][j]-V[i-1][j-i])%30103;
            else
                V[i][j]=(V[i][j-1]+V[i-1][j])%30103;
            if(V[i][j]<0)
                V[i][j]+=30103;
        }
    }
    fprintf(g,"%d",V[N][K]);
    fclose(f);
    fclose(g);
    return 0;
}
