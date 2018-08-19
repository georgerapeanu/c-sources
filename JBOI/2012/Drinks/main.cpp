#include <iostream>
#include <queue>
using namespace std;
int R,C;
string S[105];
int d=1;
int dist[5][5];
int D[105][105];
int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};
bool U[5];
int rez=1<<30;
void bfs(int val,int x,int y)
{
    for(int i=1;i<=R;i++)
        for(int j=1;j<=C;j++)
            D[i][j]=0;
    queue<int> Qx,Qy;
    Qx.push(x);Qy.push(y);
    D[x][y]=1;
    while(!Qx.empty())
    {
        x=Qx.front();Qx.pop();
        y=Qy.front();Qy.pop();
        if('0'<=S[x][y]&&S[x][y]<='9')
        {
            dist[val][S[x][y]-'0']=D[x][y]-1;
        }
        for(int k=0;k<4;k++)
        {
            int xx=x+dx[k];
            int yy=y+dy[k];
            if(xx&&yy&&xx<=R&&y<=C&&!D[xx][yy]&&S[xx][yy]!='#')
            {
                D[xx][yy]=D[x][y]+1;
                Qx.push(xx);
                Qy.push(yy);
            }
        }
    }
}
void btr(int pas,int cost,int u)
{
    if(pas>=d)
    {
        rez=min(rez,cost+dist[u][4]);return ;
    }
    for(int i=1;i<d;i++)
    {
        if(!U[i]&&dist[u][i]!=(1<<30))
        {
            U[i]=1;
            btr(pas+1,cost+dist[u][i],i);
            U[i]=0;
        }
    }
}
int main()
{
    cin>>R>>C;
    for(int i=1;i<=R;i++)
    {
        cin>>S[i];
        S[i]=" "+S[i];
        for(int j=1;j<=C;j++)
        {
            if(S[i][j]=='S')S[i][j]='0';
            if(S[i][j]=='D'){S[i][j]='0'+d;d++;}
            if(S[i][j]=='B'){S[i][j]='4';}
        }
    }
    for(int i=0;i<5;i++)for(int j=0;j<5;j++)dist[i][j]=1<<30;
    for(int i=1;i<=R;i++)
    {
        for(int j=1;j<=C;j++)
        {
            if('0'<=S[i][j]&&S[i][j]<='9')
            {
                bfs(S[i][j]-'0',i,j);
            }
        }
    }
    btr(1,0,0);
    cout<<(rez!=(1<<30) ? rez:-1);
    return 0;
}
