#include <cstdio>
#include <queue>
using namespace std;
FILE *f=fopen("inginer.in","r"),*g=fopen("inginer.out","w");
queue <int> Qx,Qy;
int N,m,stx,sty,sfx,sfy,i,j,A[80][80],D[80][80];
char c;
const int dirx[]={-1,0,1,0},diry[]={0,1,0,-1};
int Lee(int M[][80],int x1,int y1,int x2,int y2)
{
    M[x1][y1]=M[x2][y2]=0;
    Qx.push(x1);
    Qy.push(y1);
    while(!Qx.empty())
    {
        int x,y,xx,yy;
        x=Qx.front();
        y=Qy.front();
        Qx.pop();
        Qy.pop();
        for(int i=0;i<4;i++)
        {
            xx=x+dirx[i];
            yy=y+diry[i];
            if(xx>=0&&xx<=N+1&&yy>=0&&yy<=m+1)
            {
                if(M[xx][yy]==0)
                {
                    M[xx][yy]=M[x][y]+1;
                    Qx.push(xx);
                    Qy.push(yy);
                }
            }
        }
    }
    return M[x2][y2];
}
void r()
{
    for(int i=0;i<=N+1;i++)
    {
        for(j=0;j<=m+1;j++)
        {
           D[i][j]=A[i][j];
        }
    }
}
int main()
{
    fscanf(f,"%d%d",&N,&m);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%c",&c);
        for(j=1;j<=m;j++)
        {
            fscanf(f,"%c",&c);
            if(c=='X')
            {
                A[i][j]=-1;
            }
        }
    }
    fscanf(f,"%d%d%d%d",&stx,&sty,&sfx,&sfy);
    while(stx&&sty&&sfx&&sfy)
    {
        r();
        fprintf(g,"%d\n",Lee(D,stx,sty,sfx,sfy));
        fscanf(f,"%d%d%d%d",&stx,&sty,&sfx,&sfy);
    }
    fclose(f);
    fclose(g);
    return 0;
}
