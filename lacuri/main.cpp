#include <cstdio>
#include <queue>
#include <cmath>
#include <vector>
#define x first
#define y second
using namespace std;
FILE *f=fopen("lacuri.in","r"),*g=fopen("lacuri.out","w");
queue <int> Qx,Qy;
typedef pair<int,int> point;
const int dirx[]={-1,0,1,0},diry[]={0,1,0,-1};
const int dirx0[]={-1,-1,0,1,1,1,0,-1},diry0[]={0,1,1,1,0,-1,-1,-1};
int M[110][110],n,i,j,nr,A[110][110];
point rez,stsus,drsus,drjos,stjos;
vector <point> D[110][110];
bool adev=1;
void Fill(int x,int y);
void copiere(int x,int y,int xx,int yy)
{
    for(std::vector<point>::iterator it=D[x][y].begin();it!=D[x][y].end();it++)
    {
        D[xx][yy].push_back(*it);
    }
}
bool patrat(int x,int y,int l)
{
    for(int i=x;i<=x+l-1;i++)
    {
        for(int j=y;j<=y+l-1;j++)
        {
            if(M[i][j]==0)
            {
                Fill(x,y);
                return false;
            }
        }
    }
    Fill(x,y);
    return true;
}
void Lee()
{
    int x,y;
    Qx.push(1);
    Qy.push(1);
    while(!Qx.empty())
    {
        x=Qx.front();
        y=Qy.front();
        Qx.pop();
        Qy.pop();
        for(int i=0;i<4;i++)
        {
            int xx,yy;
            xx=x+dirx[i];
            yy=y+diry[i];
            if(xx&&yy&&xx<=n&&yy<=n)
            {
                if(A[xx][yy]==0)
                {
                    A[xx][yy]=A[x][y]+1;
                    copiere(x,y,xx,yy);
                    D[xx][yy].push_back(point(x,y));
                    Qx.push(xx);
                    Qy.push(yy);
                }
            }
        }
    }
}
void Fill(int x,int y)
{
    int ux=0,uy=0;
    Qx.push(x);
    Qy.push(y);
    while(!Qx.empty())
    {
        x=Qx.front();
        y=Qy.front();
        if(x<=stsus.x&&y<=stsus.y) stsus=point(x,y);
        if(x<=drsus.x&&y>=drsus.y) drsus=point(x,y);
        if(x>=stjos.x&&y<=stjos.y) stjos=point(x,y);
        if(x>=drjos.x&&y>=drjos.y) drjos=point(x,y);
        Qx.pop();
        Qy.pop();
        for(int i=0;i<8;i++)
        {
            int xx,yy;
            xx=x+dirx0[i];
            yy=y+diry0[i];
            if(xx&&yy&&xx<=n&&yy<=n)
            {
                if(M[xx][yy]==1)
                {
                    M[xx][yy]=0;
                    Qx.push(xx);
                    Qy.push(yy);
                }
            }
        }
    }
}
int main()
{
    fscanf(f,"%d",&n);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            fscanf(f,"%d",&M[i][j]);
            A[i][j]=M[i][j]*-1;
        }
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(M[i][j]==1)
            {
                int l=1;
                stsus=point(n,n);
                drsus=point(n,1);
                stjos=point(1,n);
                drjos=point(1,1);
                while((M[i+l-1][j]==1||M[i][j+l-1]==1)&&i+l-1<=n&&j+l-1<=n)
                l++;
                l--;
                if(patrat(i,j,l)==true&&(stsus.x==drsus.x&&drsus.y==drjos.y&&drjos.x==stjos.x&&stjos.y==stsus.y))
                nr++;
                else
                adev=false;
            }
        }
    }
    fprintf(g,"%d\n",nr);
    if(adev==1)
    {
        Lee();
        for(i=0;i<A[n][n];i++)
        {
            fprintf(g,"%d %d\n",D[n][n][i].first,D[n][n][i].second);
        }
        fprintf(g,"%d %d",n,n);
    }
    fclose(f);
    fclose(g);
    return 0;
}
