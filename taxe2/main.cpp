#include <fstream>
#define inf 99999
#include <queue>
using namespace std;
ifstream f("taxe1.in");
ofstream g("taxe1.out");
int a[105][105],n,s,d[105][105],i,j,x,y;
queue<int> Qx,Qy;
const int dirx[]={-1,0,1,0},diry[]={0,1,0,-1};
void initializare()
{
    for(int i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            d[i][j]=inf;
        }
    }
}
bool posibil(int x,int y)
{
    if(x<=n&&x>0&&y>0&&y<=n)
    return 1;
    return 0;
}
int main()
{
    f>>s>>n;
    initializare();
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            f>>a[i][j];
        }
    }
    d[1][1]=a[1][1];
    Qx.push(1);
    Qy.push(1);
    while(!Qx.empty())
    {
        x=Qx.front();
        y=Qy.front();
        Qx.pop();
        Qy.pop();
        for(i=0;i<4;i++)
        {
            if(posibil(x+dirx[i],y+diry[i]))
            {
                if(d[x][y]+a[x+dirx[i]][y+diry[i]]<d[x+dirx[i]][y+diry[i]])
                {
                    Qx.push(x+dirx[i]);
                    Qy.push(y+diry[i]);
                    d[x+dirx[i]][y+diry[i]]=d[x][y]+a[x+dirx[i]][y+diry[i]];
                }
            }
        }
    }
    g<<(s-d[n][n]>=0 ? s-d[n][n]:-1);
    f.close();
    g.close();
    return 0;
}
