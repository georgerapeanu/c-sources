#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("partii.in","r");
FILE *g=fopen("partii.out","w");
int V[1005][1005];
short st[1005][1005];
short sus[1005][1005];
short jos[1005][1005];
short dr[1005][1005];
int N,M;
int rez;
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            fscanf(f,"%d",&V[i][j]);
            st[i][j]=(V[i][j]>V[i][j-1])*st[i][j-1]+1;
            sus[i][j]=(V[i][j]>V[i-1][j])*sus[i-1][j]+1;
        }
    }
    for(int i=N;i;i--)
    {
        for(int j=M;j;j--)
        {
            dr[i][j]=(V[i][j]>V[i][j+1])*dr[i][j+1]+1;
            jos[i][j]=(V[i][j]>V[i+1][j])*jos[i+1][j]+1;
        }
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            rez=max(rez,st[i][j]+sus[i][j]+dr[i][j]+jos[i][j]-3);
        }
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
