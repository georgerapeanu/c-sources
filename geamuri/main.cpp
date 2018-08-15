#include <cstdio>
using namespace std;
FILE *f=fopen("geamuri.in","r");
FILE *g=fopen("geamuri.out","w");
int V[1026][1026];
int fr[50005];
int X1,X2,Y1,Y2;
int N,K,C;
int main()
{
    fscanf(f,"%d",&C);
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d%d%d%d",&X1,&Y1,&X2,&Y2);
        V[X1][Y1]++;
        V[X1][Y2+1]--;
        V[X2+1][Y1]--;
        V[X2+1][Y2+1]++;
    }
    for(int i=1;i<=C;i++)
        for(int j=1;j<=C;j++)
        {V[i][j]+=V[i-1][j]+V[i][j-1]-V[i-1][j-1];fr[V[i][j]]++;}
    fscanf(f,"%d",&K);
    for(int i=1;i<=K;i++)
    {
        fscanf(f,"%d",&X1);
        fprintf(g,"%d\n",fr[X1]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
