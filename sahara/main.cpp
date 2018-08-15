#include <cstdio>
#include <queue>
using namespace std;
FILE *f=fopen("sahara.in","r");
FILE *g=fopen("sahara.out","w");
int N,M,Q;
int T;
int V[1005][1005],rez;
queue<int> Qx,Qy;
const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};
int fl(int x,int y)
{
    Qx.push(x);
    Qy.push(y);
    int nr=0;
    V[x][y]=0;
    while(!Qx.empty())
    {
        int x=Qx.front();Qx.pop();
        int y=Qy.front();Qy.pop();
        nr++;
        for(int i=0;i<4;i++)
        {
            int xx=x+dx[i],yy=y+dy[i];
            if(V[xx][yy]>=Q)
            {
                V[xx][yy]=0;
                Qx.push(xx);
                Qy.push(yy);
            }
        }
    }
    return nr;
}
int main()
{
    fscanf(f,"%d%d%d",&N,&M,&Q);
    fscanf(f,"%d",&T);
    for(int i=1;i<=T;i++)
    {
        int x,xx,y,yy,val;
        fscanf(f,"%d%d%d%d%d",&x,&y,&xx,&yy,&val);
        V[x][y]+=val;V[xx+1][yy+1]+=val;V[x][yy+1]-=val;V[xx+1][y]-=val;
    }
    for(int i=1;i<=N+1;i++) for(int j=1;j<=M+1;j++) V[i][j]+=(V[i-1][j]+V[i][j-1]-V[i-1][j-1]);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            if(V[i][j]>=Q)
            {
                int nr=fl(i,j);
                rez=max(rez,nr);
            }
        }
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
}

