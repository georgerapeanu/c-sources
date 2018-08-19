#include <iostream>
#include <queue>
#include <stack>
using namespace std;
char de[]="URDL";
int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};
int x=1,y=1,nx,ny;
queue<int> Qx,Qy;
int N,M;
char C[105][105];
int ant[105][105];
bool viz[105][105];
stack<char> S;
bool sx,sy;
int main()
{
    cin>>N>>M;
    for(int i=0;i<=N;i++)cin.getline(C[i]+1,105);
    Qx.push(x);
    Qy.push(y);
    ant[x][y]=-1;
    viz[x][y]=1;
    while(!Qx.empty())
    {
        x=Qx.front();Qx.pop();
        y=Qy.front();Qy.pop();
        for(int k=0;k<4;k++)
        {
            nx=x+dx[k];
            ny=y+dy[k];
            if(!viz[nx][ny]&&nx&&ny&&nx<=N&&ny<=M&&C[nx][ny]!='*')
            {
                ant[nx][ny]=k;
                viz[nx][ny]=1;
                Qx.push(nx);
                Qy.push(ny);
            }
        }
    }
    x=y=0;
    for(int i=1;i<=N&&!x;i++)
        for(int j=1;j<=M&&!x;j++)
            if(C[i][j]=='F'){x=i;y=j;break;}
    if(!viz[x][y])return 0;
    while(ant[x][y]!=-1&&viz[x][y])
    {
        S.push(ant[x][y]);
        x-=dx[S.top()];
        y-=dy[S.top()];
    }
    x=y=1;
    while(!S.empty())
    {
        if(!sx&&C[x-1][y]!='*'&&C[x+1][y]!='*')
        {
            sx=1;
            cout<<"U\n";cout.flush();
            cin>>nx>>ny;
            if(nx>x)swap(de[0],de[2]);
            if(nx!=x)
            {
                cout<<"D\n";cout.flush();
                cin>>nx>>ny;
            }
        }
        if(!sy&&C[x][y-1]!='*'&&C[x][y+1]!='*')
        {
            sy=1;
            cout<<"L\n";cout.flush();
            cin>>nx>>ny;
            if(ny>y)swap(de[1],de[3]);
            if(ny!=y)
            {
                cout<<"R\n";cout.flush();
                cin>>nx>>ny;
            }
        }
        cout<<de[S.top()]<<"\n";
        cout.flush();
        cin>>x>>y;
        S.pop();
    }
    return 0;
}
