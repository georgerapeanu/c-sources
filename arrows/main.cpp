#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
FILE *f=fopen("arrows.in","r");
FILE *g=fopen("arrows.out","w");
bool favorabil[505][505],actu[505][505];
int viz[505][505],V[505][505];
short C[505][505];
const int dx[]={0,0,-1,0,1};
const int dy[]={0,1,0,-1,0};
int c,N,M,serie,rez,lin,col,b;
struct point{int x,y;};
vector<point> tmp;
void afla(int i,int j,int serie)
{
    if(viz[i][j]==serie||favorabil[i][j])
    {favorabil[i][j]=1;return;}
    if(viz[i][j])
        return ;
    viz[i][j]=serie;
    int x,y;
    x=i+dx[C[i][j]];
    y=j+dy[C[i][j]];
    afla(x,y,serie);
    V[i][j]=V[x][y]+1;
    favorabil[i][j]=favorabil[x][y];
}
void act(int i,int j)
{
    if(actu[i][j])
    {
        int l=0;
        while(tmp[l].x!=i||tmp[l].y!=j)
            l++;
        for(int ind=l;ind<tmp.size();ind++)
            V[tmp[ind].x][tmp[ind].y]=tmp.size()-l;
        for(int ind=l-1;ind>=0;ind--)
            V[tmp[ind].x][tmp[ind].y]=V[tmp[ind+1].x][tmp[ind+1].y]+1;
    }
    else
    {
        tmp.push_back({i,j});
        int x,y;
        actu[i][j]=1;
        x=i+dx[C[i][j]];
        y=j+dy[C[i][j]];
        if(viz[x][y]==serie)
        {
            act(x,y);
        }
    }
}
int main()
{
    fscanf(f,"%d%d%d",&c,&N,&M);
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            fscanf(f,"%d",&C[i][j]);
    for(int i=0;i<=N+1;i++)
    {
        viz[i][0]=viz[i][M+1]=1;
    }
    for(int i=0;i<=M+1;i++)
    {
        viz[0][i]=viz[N+1][i]=1;
    }
    serie=1;
    fscanf(f,"%d%d",&lin,&col);
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            {
                if(!viz[i][j])
                {
                    serie++;
                    afla(i,j,serie);
                    if(favorabil[i][j])
                    {
                        tmp.clear();
                        act(i,j);
                    }
                }
                b+=favorabil[i][j];
                rez=max(rez,V[i][j]*(favorabil[i][j]==1 ? 1000:1));
            }
    if(c==1)
    {
        fprintf(g,"%d",V[lin][col]*(favorabil[lin][col]==1 ? 1000:1));
    }
    else if(c==2)
    {
        fprintf(g,"%d",b);
    }
    else
    {
        fprintf(g,"%d",rez);
    }
    fclose(f);
    fclose(g);
    return 0;
}
