#include <cstdio>
#include <queue>
using namespace std;
FILE *f=fopen("teme.in","r");
FILE *g=fopen("teme.out","w");
int N,M,A,B,i,j,k,nr;
bool m[305][305],viz[305];
queue <int> Q;
void dfs(int nod)
{
     viz[nod]=1;
    for(int i=1;i<=N;i++)
    {
        if(!viz[i]&&m[nod][i])
        {
            dfs(i);
        }
    }
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%d %d",&A,&B);
        m[A][B]=m[B][A]=1;
    }
    for(k=1;k<=N;k++)
    {
        for(i=1;i<=N;i++)
        {
            for(j=1;j<=N;j++)
            {
                if(k!=i&&k!=j&&i!=j)
                {
                  if(m[i][k]&&m[k][j])
                        m[i][j]=1;
                }
            }
        }
    }
    for(i=1;i<=N;i++)
    {
        if(!viz[i])
        {
            dfs(i);
            nr++;
        }
    }
    fprintf(g,"%d",nr);
    return 0;
}
