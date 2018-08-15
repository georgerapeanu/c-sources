#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
int dist[25][25];
queue<int> Qx,Qy;
int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};
int N,R,K;
char V[305][25][25];
pair<int,int> L[305][15];
int nr[305];
int C[305][15];
int dp[305][3005];
int getcost(int lvl)
{
    int nr=0;
    while(!Qx.empty())
    {
        int x=Qx.front();Qx.pop();
        int y=Qy.front();Qy.pop();
        nr++;
        for(int k=0;k<4;k++)
        {
            int xx=x+dx[k],yy=y+dy[k];
            if(xx&&yy&&xx<=R&&yy<=R&&!dist[xx][yy]&&V[lvl][xx][yy]<=V[lvl][x][y]&&V[lvl][xx][yy]!='L')
            {
                dist[xx][yy]=1+dist[x][y];
                Qx.push(xx);
                Qy.push(yy);
            }
        }
    }
    memset(dist,0,sizeof(dist));
    return nr;
}
int main()
{
    cin>>N>>K>>R;
    for(int i=1;i<=N;i++)
    {
        for(int j=0;j<=R;j++)
        {
            cin.getline(V[i][j]+1,25);
            for(int k=1;k<=R;k++)if(V[i][j][k]=='L')L[i][++nr[i]]={j,k};
        }
        for(int j=0;j<=10;j++)C[i][j]=1<<30;
        if(!nr[i])continue;
        for(int conf=0;conf<(1<<nr[i]);conf++)
        {
            int nrbiti=0;
            for(int j=1;j<=nr[i];j++)
            {
                if(!((conf>>(j-1))&1))
                {
                    dist[L[i][j].first][L[i][j].second]=1;
                    Qx.push(L[i][j].first);
                    Qy.push(L[i][j].second);
                }
                else
                    nrbiti++;
            }
            C[i][nrbiti]=min(C[i][nrbiti],getcost(i));
        }
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=0;j<=K;j++)
        {
            dp[i][j]=1<<30;
            for(int l=0;l<=j&&l<=nr[i];l++)
            {
                dp[i][j]=min(dp[i][j],dp[i-1][j-l]+C[i][l]);
            }
        }
    }
    cout<<N*R*R-dp[N][K];
    return 0;
}
