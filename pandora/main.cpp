#include <cstdio>
#include <algorithm>
#include <queue>
#define bun(x,y) (0<x&&x<=N&&0<y&&y<=N)
#define nx (x+dx[k])
#define ny (y+dy[k])
using namespace std;
FILE *f=fopen("pandora.in","r");
FILE *g=fopen("pandora.out","w");
short pat[1001][1001],sus[1001][1001],st[1001][1001],V[1001][1001];
int N,K,M,x,y,c;
bool ok;
const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};
bool forma(int i,int j)
{
    return (pat[i-1][j-1]==K-2&&st[i][j-1]==K-2&&sus[i-1][j]==K-2&&st[i-K+1][j-1]==K-2&&sus[i-1][j-K+1]==K-2);
}
bool egale(int i,int j)
{
    return (V[i-1][j-1]&&V[i-1][j-1]==V[i][j-1]&&V[i-1][j-1]==V[i-1][j]&&V[i-1][j-1]==V[i-K+1][j-1]&&V[i-1][j-1]==V[i-1][j-K+1]);
}
bool maimari(int i,int j)
{
    return (V[i-1][j-1]>V[i][j]&&V[i-1][j-1]>V[i-K+1][j]&&V[i-1][j-1]>V[i][j-K+1]&&V[i-1][j-1]>V[i-K+1][j-K+1]);
}
void fillitbaby(int x,int y)
{
    queue<int> Qx,Qy;
    Qx.push(x);
    Qy.push(y);
    V[x][y]=0;
    while(!Qx.empty())
    {
        int x=Qx.front();Qx.pop();
        int y=Qy.front();Qy.pop();
        for(int k=0;k<4;k++)
        {
            if(bun(nx,ny)&&V[nx][ny])
            {
                V[nx][ny]=0;
                Qx.push(nx);
                Qy.push(ny);
            }
        }
    }
}
int main()
{
    fscanf(f,"%d%d%d",&N,&K,&M);
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d%d%d",&x,&y,&c);
        V[x][y]=c;
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            pat[i][j]=min(pat[i-1][j-1],min(pat[i][j-1],pat[i-1][j]))*(V[i][j]==V[i-1][j]&&V[i][j]==V[i-1][j-1]&&V[i][j]==V[i][j-1])+1;
            sus[i][j]=sus[i-1][j]*(V[i][j]==V[i-1][j])+1;
            st[i][j]=st[i][j-1]*(V[i][j]==V[i][j-1])+1;
        }
    }
    for(int i=K;i<=N;i++)
    {
        for(int j=K;j<=N;j++)
        {
                if(forma(i,j)&&egale(i,j)&&maimari(i,j))
                    fprintf(g,"%d %d\n",i-K+1,j-K+1),ok=1,fillitbaby(i,j);
        }
    }
    if(!ok)
        fputc('0',g);
    fclose(f);
    fclose(g);
    return 0;
}
