#include <iostream>
#include <queue>
using namespace std;
int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};
pair<int,int> D[1005][1005][4];
char C[1005][1005];
int N,M,K;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N>>M>>K;
    for(int i=0;i<=N;i++)
    {
        cin.getline(C[i]+1,1005);
    }
    int X,Y,XX,YY;
    cin>>X>>Y>>XX>>YY;
    if(X==XX&&Y==YY){cout<<0;return 0;}
    if(C[X][Y]=='#'){cout<<-1;return 0;}
    D[X][Y][0]={1,0};D[X][Y][1]={1,0};D[X][Y][2]={1,0};D[X][Y][3]={1,0};
    queue<pair<pair<pair<int,int>,int>,pair<int,int> > > Q;
    Q.push({{{X,Y},0},{1,0}});Q.push({{{X,Y},1},{1,0}});Q.push({{{X,Y},2},{1,0}});Q.push({{{X,Y},3},{1,0}});
    while(!Q.empty())
    {
        pair<pair<pair<int,int>,int>,pair<int,int> > tmp=Q.front();Q.pop();
        if(D[tmp.first.first.first][tmp.first.first.second][tmp.first.second]!=tmp.second)continue;
        int X=tmp.first.first.first,Y=tmp.first.first.second,dir=tmp.first.second;
        for(int i=0;i<4;i++)
        {
            int nX=X+dx[i];
            int nY=Y+dy[i];
            if(nX&&nY&&nX<=N&&nY<=M&&C[nX][nY]=='.')
            {
                pair<int,int> cost;
                cost.first=D[X][Y][dir].first+(dir!=i||D[X][Y][dir].second==K);
                cost.second=(dir!=i||D[X][Y][dir].second==K ? 1:D[X][Y][dir].second+1);
                if(cost==make_pair(0,0))continue;
                if(cost<D[nX][nY][i]||D[nX][nY][i]==make_pair(0,0))
                {
                    D[nX][nY][i]=cost;
                    Q.push({{{nX,nY},i},cost});
                }
            }
        }
    }
    pair<int,int> cost={0,0};
    for(int i=0;i<4;i++)
    {
        if((D[XX][YY][i]<cost||cost==make_pair(0,0))&&D[XX][YY][i]!=make_pair(0,0))
        {
            cost=D[XX][YY][i];
        }
    }
    cout<<(cost==make_pair(0,0) ? -1:cost.first);
    return 0;
}
