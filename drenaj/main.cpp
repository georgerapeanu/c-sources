#include <cstdio>
#include <queue>
using namespace std;
FILE *f=fopen("drenaj.in","r");
FILE *g=fopen("drenaj.out","w");
bool notok[150][150];
queue <int> Qx,Qy;
int i,j,N,M,V[150][150],nr;
const int dirx[]={-1,0,1,0},diry[]={0,1,0,-1};
void umple(int x,int y,int val)
{
    int xx,yy;
    Qx.push(x);
    Qy.push(y);
    while(!Qx.empty())
    {
        x=Qx.front();
        y=Qy.front();
        Qx.pop();
        Qy.pop();
        notok[x][y]=1;
        for(int i=0;i<=3;i++)
        {
            xx=x+dirx[i];
            yy=y+diry[i];
            if(V[xx][yy]==val&&notok[xx][yy]==0)
            {
                Qx.push(xx);
                Qy.push(yy);
            }
        }
    }
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N;i++)
        for(j=1;j<=M;j++)
            fscanf(f,"%d",&V[i][j]);
    //bordare
    for(i=0;i<=N+1;i++)
        V[i][0]=V[i][M+1]=10001;
    for(i=1;i<=M;i++)
        V[0][i]=V[N+1][i]=10001;
    //final bordare
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            if(V[i][j]>V[i-1][j]||V[i][j]>V[i][j+1]||V[i][j]>V[i][j-1]||V[i][j]>V[i+1][j]&&!notok[i][j])
                umple(i,j,V[i][j]);
        }
    }
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            if(!notok[i][j])
            {
                nr++;
                umple(i,j,V[i][j]);
            }
        }
    }
    fprintf(g,"%d",nr);
    fclose(f);
    fclose(g);
    return 0;
}
