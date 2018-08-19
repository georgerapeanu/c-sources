#include <cstdio>
#include <queue>
using namespace std;
queue <long long> Qx,Qy;
FILE *f=fopen("taxa.in","r"),*g=fopen("taxa.out","w");
long long i,j,N,M,m[1001][1001],stx,sty,drx,dry,d[1001][1001];
const int dirx[]={-1,-1,0,1,1,1,0,-1},diry[]={0,1,1,1,0,-1,-1,-1};
void Lee()
{
    Qx.push(stx);
    Qy.push(sty);
    long long x=0,y=0;
    while(!Qx.empty())
    {
        x=Qx.front();
        y=Qy.front();
        Qx.pop();
        Qy.pop();
        for(i=0;i<8;i++)
        {
            long long xx=0,yy=0;
            xx=x+dirx[i];
            yy=y+diry[i];
            if(xx&&yy&&xx<=N&&y<=N)
            {
                if(m[x][y]==m[xx][yy])
                {
                    if(d[xx][yy]>d[x][y])
                    {
                        d[xx][yy]=d[x][y];
                        Qx.push(xx);
                        Qy.push(yy);
                    }
                }
                else
                {
                    if(d[xx][yy]>=m[x][y]*m[xx][yy]+d[x][y])
                    {
                        d[xx][yy]=m[x][y]*m[xx][yy]+d[x][y];
                        Qx.push(xx);
                        Qy.push(yy);
                    }
                }
            }
        }
    }
}
int main()
{
    fscanf(f,"%lld%lld%lld%lld%lld%lld",&N,&M,&stx,&sty,&drx,&dry);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            fscanf(f,"%lld",&m[i][j]);
        }
    }
    for(i=1;i<=N;i++)
        for(j=1;j<=M;j++)
            d[i][j]=12000;
    d[stx][sty]=0;
    Lee();
    fprintf(g,"%lld",d[drx][dry]);
    fclose(f);
    fclose(g);
    return 0;
}
