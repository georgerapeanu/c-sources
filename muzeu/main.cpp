/*#include <cstdio>
#include <queue>
using namespace std;
FILE *f=fopen("muzeu.in","r"),*g=fopen("muzeu.out","w");
int n,m[260][260],i,j;
const int dirx[]={-1,0,1,0},diry[]={0,1,0,-1};
char c;
queue<int> Qx,Qy;
int main()
{
    fscanf(f,"%d",&n);
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%c",&c);
        for(j=1;j<=n;j++)
        {
            fscanf(f,"%c",&c);
            if(c=='#')
            m[i][j]=-2;
            else if(c=='P')
            {
                Qx.push(i);
                Qy.push(j);
            }
            else
            m[i][j]=-1;
        }
    }
    fclose(f);
    while(!Qx.empty())
    {
        int x,y;
        x=Qx.front();
        y=Qy.front();
        Qx.pop();
        Qy.pop();
        for(i=0;i<4;i++)
        {
            int xx,yy;
            xx=x+dirx[i];
            yy=y+diry[i];
            if(yy&&xx&&xx<=n&&y<=n)
            {
                if(m[xx][yy]==-1)
                {
                    m[xx][yy]=m[x][y]+1;
                    Qx.push(xx);
                    Qy.push(yy);
                }
            }
        }
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            fprintf(g,"%d ",m[i][j]);
        fprintf(g,"\n");
    }
    fclose(g);
    return 0;
}*/
#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("muzeu.in","r");
FILE *g=fopen("muzeu.out","w");
int i,N,K,a,b,A,B;
int main()
{
    fscanf(f,"%d%d",&N,&K);
    A=K;
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d %d",&a,&b);
        if(b>=B)
        {
            A-=(b-B);
            B=b;
        }
        else if(b<B&&a>=B-b)
        {
            A=A+B-b;
            B=K-A;
        }
        else
        {
            B=B-a;
            A=A+a;
        }
    }
    fprintf(g,"%d",A);
    fclose(f);
    fclose(g);
    return 0;
}

