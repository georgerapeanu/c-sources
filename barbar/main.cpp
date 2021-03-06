#include <queue>
#include <cstdio>
using namespace std;
FILE *f=fopen("barbar.in","r");
FILE *g=fopen("barbar.out","w");
const int dirx[]={-1,0,1,0},diry[]={0,1,0,-1};
queue <int> Qx,Qy;
int M,stx,sty,fnx,fny,N,i,j,V[1010][1010],x,y,xx,yy;
char c;
bool ispossible(int nr)
{
    while(!Qx.empty())
    {
        Qx.pop();
        Qy.pop();
    }
    Qx.push(stx);
    Qy.push(sty);
    while(!Qx.empty())
    {
        x=Qx.front();
        y=Qy.front();
        Qx.pop();
        Qy.pop();
        for(i=2;i<=3;i++)
            //verific daca merge
            //dupa asta cautare binara;
    }
}
int main()
{
    fscanf(f,"%d %d\n",&N,&M);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            c=fgetc(f);
            if(c=='D')
            {
                Qx.push(i);
                Qy.push(j);
            }
            else if(c=='O')
            {
                fnx=i;
                fny=j;
            }
            else if(c=='I')
            {
                stx=i;
                sty=j;
            }
            else if(c=='*')
            V[i][j]=-1;
        }
        c=fgetc(f);
    }
    for(i=1;i<=N;i++)
        V[i][0]=V[i][N+1]=-1;
    for(i=1;i<=M;i++)
        V[0][i]=V[N+1][i]=-1;
    while(!Qx.empty())
    {
        x=Qx.front();
        Qx.pop();
        y=Qy.front();
        Qy.pop();
        for(i=0;i<=3;i++)
        {
            xx=x+dirx[i];
            yy=y+diry[i];
            if(!V[xx][yy])
            {
                V[xx][yy]=V[x][y]+1;
                Qx.push(xx);
                Qy.push(yy);
            }
        }
    }
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            fprintf(g,"%d ",V[i][j]);
        }
        fprintf(g,"\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
