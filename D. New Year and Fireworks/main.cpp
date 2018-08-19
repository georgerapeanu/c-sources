#include <iostream>
#include <set>
using namespace std;
set <pair<int,int> > viz;
bool m[7][31][8][312][312];
int T[35],xmin=1<<30,ymin=1<<30,xmax,ymax;
int N;
int X[8]={-1,-1,0,1,1,1,0,-1};
int Y[8]={0,1,1,1,0,-1,-1,-1};
void dfs(int x,int y,int dir,int pas)
{
    if(pas>N)
        return ;
    for(int i=0;i<=T[pas];i++)
    {
        int lg=T[pas]-i;
        if(m[lg][pas][dir][x][y])
            return ;
        m[lg][pas][dir][x][y]=1;
        viz.insert(make_pair(x,y));
        if(i!=T[pas])
        {
            x+=X[dir];
            y+=Y[dir];
        }
    }
    dfs(x,y,(7+dir)%8,pas+1);
    dfs(x,y,(dir+1)%8,pas+1);
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>T[i];
    }
    T[1]--;
    dfs(154,154,0,1);
    cout<<viz.size();
    return 0;
}
