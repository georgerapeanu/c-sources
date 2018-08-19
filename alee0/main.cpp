#include <cstdio>
#include <queue>
using namespace std;
FILE *f=fopen("alee.in","r");
FILE *g=fopen("alee.out","w");
int N,M,m[180][180],X,Y,i,j,x1,y1,x2,y2;
const int dirx[]={0,-1,0,1,0},diry[]={0,0,1,0,-1};
queue<int> Qx,Qy;
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%d %d",&X,&Y);
        m[X][Y]=-1;
    }
    fscanf(f,"%d %d %d %d",&x1,&y1,&x2,&y2);
    for(i=0;i<=N+1;i++)
    {
        m[i][0]=m[0][i]=m[i][N+1]=m[N+1][i]=-1;
    }
    Qx.push(x1);
    Qy.push(y1);
    m[x1][y1]=1;
    while(!Qx.empty())
    {
        int x=Qx.front();
        int y=Qy.front();
        Qx.pop();
        Qy.pop();
        for(i=1;i<=4;i++)
        {
            if(m[x+dirx[i]][y+diry[i]]==0)
            {
                m[x+dirx[i]][y+diry[i]]=m[x][y]+1;
                Qx.push(x+dirx[i]);
                Qy.push(y+diry[i]);
            }
        }
    }
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=N;j++)
        {
            printf("%d ",m[i][j]);
        }
        printf("\n");
    }
    fprintf(g,"%d",m[x2][y2]);
    return 0;
}
