#include <iostream>
#include <queue>
using namespace std;
int mat[1005][1005];
int tmp[1005][1005];
int dist[1005][1005];
int H,W,stx,sty,drx,dry;
int N,M;
const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};
int main() {
    cin>>N>>M;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            cin>>tmp[i][j];
        }
    }
    cin>>H>>W>>stx>>sty>>drx>>dry;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            if(tmp[i][j])
            {
                mat[i+1][j+1]++;
                mat[max(i-H+1,1)][max(1,j-W+1)]++;
                mat[i+1][max(1,j-W+1)]--;
                mat[max(i-H+1,1)][j+1]--;
            }
        }
    }
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            mat[i][j]+=mat[i-1][j]+mat[i][j-1]-mat[i-1][j-1];
    queue<int> Qx,Qy;Qx.push(stx);Qy.push(sty);
    dist[stx][sty]=1;
    while(!Qx.empty())
    {
        int x,y;
        x=Qx.front();Qx.pop();
        y=Qy.front();Qy.pop();
        for(int k=0;k<4;k++)
        {
            int nx=x+dx[k],ny=y+dy[k];
            if(nx&&ny&&nx<=N&&ny<=M&&dist[nx][ny]==0&&mat[nx][ny]==0&&nx+H-1<=N&&ny+W-1<=M)
            {
                dist[nx][ny]=dist[x][y]+1;
                Qx.push(nx);
                Qy.push(ny);
            }
        }
    }
    if(dist[drx][dry]==0)cout<<-1;
    else cout<<dist[drx][dry]-1;
    return 0;
}
