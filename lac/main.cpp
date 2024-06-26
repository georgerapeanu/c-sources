#include <cstdio>
#include <queue>
using namespace std;
FILE *f=fopen("lac.in","r");
FILE *g=fopen("lac.out","w");
queue <int> Qx,Qy;
bool V[1005][1005];
int a,b,i,j;
int N,M;
const int dirx[]={-1,0,1,0};
const int diry[]={0,1,0,-1};
void Fil(int x,int y)
{
    Qx.push(x);
    Qy.push(y);
    V[x][y]=0;
    while(!Qx.empty())
    {
       x=Qx.front();
       y=Qy.front();
       Qx.pop();
       Qy.pop();
       for(int i=0;i<4;i++)
       {
           if(V[x+dirx[i]][y+diry[i]])
           {
               V[x+dirx[i]][y+diry[i]]=0;
               Qx.push(x+dirx[i]);
               Qy.push(y+diry[i]);
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
    for(i=1;i<=N;i++)
    {
        if(V[i][1]==1)
        {
            Fil(i,1);
            a++;
        }
        if(V[i][M])
        {
            Fil(i,M);
            a++;
        }
    }
    for(i=1;i<=M;i++)
    {
        if(V[1][i])
        {
            Fil(1,i);
            a++;
        }
        if(V[N][i])
        {
            Fil(N,i);
            a++;
        }
    }
    for(i=2;i<N;i++)
    {
        for(j=2;j<M;j++)
        {
            if(V[i][j])
            {
                Fil(i,j);
                b++;
            }
        }
    }
    fprintf(g,"%d %d",b,a);
    fclose(f);
    fclose(g);
    return 0;
}
