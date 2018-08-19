#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("defrag.in","r");
FILE *g=fopen("defrag.out","w");
int P,S,C,x,y;
int V;
int nr;
int Su[105][365];
int A[105];
int main()
{
    fscanf(f,"%d",&V);
    fscanf(f,"%d%d",&P,&S);
    fscanf(f,"%d",&C);
    nr=P;
    for(int i=1;i<=C;i++)
    {
        fscanf(f,"%d %d",&x,&y);
        nr=nr-(A[x]==0);
        A[x]++;
        Su[x][y]++;
    }
    if(V==1)
    {
        fprintf(g,"%d",nr);
    }
    else
    {
        for(int i=1;i<=P;i++)
        {
            for(int j=1;j<=S;j++)
                Su[i][j]+=Su[i][j-1];
        }
        for(int i=1;i<=P;i++)
        {
            int rez=(1<<30);
            for(int j=1;j<=S-A[i]+1;j++)
                rez=min(rez,A[i]-Su[i][j+A[i]-1]+Su[i][j-1]);
            for(int j=S-A[i]+2;j<=S;j++)
            {
                rez=min(rez,A[i]-(Su[i][S]-Su[i][j-1]+Su[i][(j+A[i]-2)%S+1]));
            }
            fprintf(g,"%d ",rez);
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
