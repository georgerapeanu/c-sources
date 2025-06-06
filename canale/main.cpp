#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
FILE *f=fopen("canale.in","r");
FILE *g=fopen("canale.out","w");
queue <int> Qu;
int D[3005][3005],u,v,w,k;
int i,j,N,M,Q;
int main()
{
    fscanf(f,"%d %d %d",&N,&M,&Q);
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%d %d %d",&u,&v,&w);
        D[u][v]=w;
        D[v][u]=w;
    }
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=N;j++)
            if(D[i][j]!=0)
                Qu.push(j);
        while(!Qu.empty())
        {
            j=Qu.front();
            Qu.pop();
            for(k=1;k<=N;k++)
            {
                if(D[j][k]!=0&&D[i][k]<min(D[i][j],D[j][k])&&k!=i)
                {
                    D[i][k]=min(D[i][j],D[j][k]);
                    Qu.push(k);
                }
            }
        }
    }
    for(i=1;i<=Q;i++)
    {
        fscanf(f,"%d %d",&u,&v);
        fprintf(g,"%d\n",D[u][v]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
