#include <cstdio>
#include <queue>
using namespace std;
FILE *f=fopen("wow.in","r");
FILE *g=fopen("wow.out","w");
queue <int> Qx,Qy;
int N,M,R,m[200][200],i,j,x,y,xx,yy,k,suma,minim,bestx,besty;
const int dirx[]={-1,0,1,0},diry[]={0,1,0,-1};
typedef struct{int x,y;} punct;
punct V[1510];
int main()
{
    fscanf(f,"%d %d %d",&N,&M,&R);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            fscanf(f,"%d",&m[i][j]);
            m[i][j]=m[i][j]*(-1);
        }
    }
    for(i=1;i<=R;i++)
    {
        fscanf(f,"%d",V[i].x,V[i].y);
    }
    for(i=0;i<=N+1;i++)
    {
        m[i][0]=m[i][N+1]=-1;
    }
    for(i=0;i<=M+1;i++)
        m[0][i]=m[N+1][i]=-1;
    Qx.push(V[1].x);
    Qy.push(V[1].y);
    while(!Qx.empty());
    {
        x=Qx.front();
        y=Qy.front();
        Qx.pop();
        Qy.pop();
        for(i=0;i<4;i++)
        {
            xx=x+dirx[i];
            yy=y+diry[i];
            if(m[xx][yy]==0)
            {
                m[xx][yy]=m[x][y]+1;
                Qx.push(xx);
                Qy.push(yy);
            }
        }
    }
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            if(m[i][j]!=-1)
            {
                for(k=1;k<=R;k++)
                {

                }
            }
        }
    }
    return 0;
}