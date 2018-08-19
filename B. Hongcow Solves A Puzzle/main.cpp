#include <iostream>
#include <queue>
using namespace std;
int N,M;
char C[505][505];
bool viz[505][505];
typedef struct{int x,y;} punct;
const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};
queue <punct> Q;
int main()
{
    cin>>N>>M;
    cin.getline(C[0],505);
    for(int i=1;i<=N;i++)
    {
        cin.getline(C[i]+1,505);
    }
    for(int i=0;i<=N+1;i++)
        viz[i][0]=viz[i][M+1]=1;
    for(int j=0;j<=M+1;j++)
        viz[0][j]=viz[N+1][j]=1;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            if(C[i][j]=='X')
            {
                int nr=0,stx=600,sty=600,drx=0,dry=0;
                Q.push({i,j});
                viz[i][j]=1;
                while(!Q.empty())
                {
                    nr++;
                    int x,y;
                    x=(Q.front()).x;
                    y=(Q.front()).y;
                    Q.pop();
                    stx=min(stx,x);
                    sty=min(sty,y);
                    drx=max(drx,x);
                    dry=max(dry,y);
                    for(int k=0;k<4;k++)
                    {
                        if(C[x+dx[k]][y+dy[k]]=='X'&&!viz[x+dx[k]][y+dy[k]])
                        {
                            viz[x+dx[k]][y+dy[k]]=1;
                            Q.push({x+dx[k],y+dy[k]});
                        }
                    }
                }
                cout<<(nr==(drx-stx+1)*(dry-sty+1)?"YES":"NO");
                return 0;
            }
    return 0;
}
