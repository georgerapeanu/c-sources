#include <iostream>
#include <set>
using namespace std;
set<int> G[200005];
int dist[200005];
int N,M;
int main()
{
    cin>>N>>M;
    for(int i=1;i<=M;i++)
    {
        int x,y;
        cin>>x>>y;
        G[x].insert(y);
        G[y].insert(x);
    }
    for(int i=1;i<=N;i++)
    {
        if(G[1].find(i)!=G[1].end()&&G[N].find(i)!=G[N].end())
        {
            cout<<"POSSIBLE";return 0;
        }
    }
    cout<<"IMPOSSIBLE";
    return 0;
}
