#include <cstdio>
#include <queue>
using namespace std;
FILE *f=fopen("oras1.in","r");
FILE *g=fopen("oras1.out","w");
char c[300][300];
int N,M,i,j,a,b,rez,k,nr;
const int dirx[]={-1,0,1,0},diry[]={0,1,0,-1};
queue <int> Qx;
queue <int> Qy;
int main()
{
    fscanf(f,"%d %d\n",&N,&M);
    for(i=1;i<=N;i++)
    {
        fgets(c[i]+1,300,f);
    }
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            if(c[i][j]!='.')
                if(c[i-1][j]=='.'||c[i-1][j+1]=='.'||c[i][j+1]=='.'||c[i+1][j+1]=='.'||c[i+1][j]=='.'||c[i+1][j-1]=='.'||c[i][j-1]=='.'||c[i-1][j-1]=='.')
                    a++;
        }
    }
    fprintf(g,"%d ",a);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            if(c[i][j]=='C')
            {
                Qx.push(i);
                Qy.push(j);
                int x=0,y=0;
                while(!Qx.empty())
                {
                    x=Qx.front();
                    y=Qy.front();
                    c[x][y]='.';
                    Qx.pop();
                    Qy.pop();
                    for(k=0;k<4;k++)
                    {
                        if(c[x+dirx[k]][y+diry[k]]=='C')
                        {
                                Qx.push(x+dirx[k]);
                                Qy.push(y+diry[k]);
                        }
                    }
                }
                b++;
            }
            else if(c[i][j]=='P')
            {
                nr=0;
                int x=0,y=0;
                 Qx.push(i);
                Qy.push(j);
                 while(!Qx.empty())
                {
                    x=Qx.front();
                    y=Qy.front();
                    c[x][y]='.';
                    nr++;
                    Qx.pop();
                    Qy.pop();
                    for(k=0;k<4;k++)
                    {
                        if(c[x+dirx[k]][y+diry[k]]=='P')
                        {
                                Qx.push(x+dirx[k]);
                                Qy.push(y+diry[k]);
                        }
                    }
                }
                rez=rez>nr?rez:nr;
            }
        }
    }
    fprintf(g,"%d %d",b,rez);
    fclose(f);
    fclose(g);
    return 0;
}
