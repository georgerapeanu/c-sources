#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define x first
#define y second
using namespace std;
char C[55][55];
int N,M;
pair<int,int> st[15];
pair<int,int> dr[15];
int dist[55][55];
int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};
int rez=1<<30,ind;
int main()
{
    scanf("%d %d\n",&M,&N);
    for(int i=1;i<=N;i++)
        fgets(C[i]+1,55,stdin);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            if(C[i][j]=='.'||C[i][j]=='#')continue;
            if(C[i][j]=='F')
            {
                if(!st[4].x)st[4]={i,j};
                dr[4]={i,j};
            }
            if(!st[C[i][j]-'0'].x)st[C[i][j]-'0']={i,j};
            dr[C[i][j]-'0']={i,j};
        }
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            if(C[i][j]=='#')
            {
                for(int k=i;k&&k>i-(dr[1].x-st[1].x+1);k--)
                    for(int l=j;l&&l>j-(dr[1].y-st[1].y+1);l--)
                        C[k][l]='#';
            }
        }
    }
    //for(int i=1;i<=N;i++)printf("%s\n",C[i]+1);
    for(int i=1;i<=3;i++)
    {
        if(!st[i].x)continue;
        memset(dist,0,sizeof(dist));
        queue<int> Qx,Qy;
        Qx.push(st[i].x);
        Qy.push(st[i].y);
        dist[st[i].x][st[i].y]=1;
        while(!Qx.empty())
        {
            int X=Qx.front();Qx.pop();
            int Y=Qy.front();Qy.pop();
            for(int k=0;k<4;k++)
            {
                int XX=X+dx[k];
                int YY=Y+dy[k];
                if(!dist[XX][YY]&&(C[XX][YY]=='.'||C[XX][YY]==i+'0'||C[XX][YY]=='F'))
                {
                    dist[XX][YY]=1+dist[X][Y];
                    Qx.push(XX);
                    Qy.push(YY);
                }
            }
        }
        if(dist[st[4].x][st[4].y]&&rez>dist[st[4].x][st[4].y])
        {
            rez=dist[st[4].x][st[4].y];
            ind=i;
        }
    }
    printf("%d\n%d",ind,rez-1);
    return 0;
}
