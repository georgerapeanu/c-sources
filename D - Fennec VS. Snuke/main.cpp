#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;
int dist[2][100005];
vector<int> G[100005];
int N;
int szA,szB;
queue<int> Q;
int main()
{
    cin>>N;
    for(int i=1;i<N;i++)
    {
        int x,y;
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dist[0][1]=1;
    Q.push(1);
    while(!Q.empty())
    {
        int nod=Q.front();Q.pop();
        for(auto it:G[nod])
        {
            if(!dist[0][it])
            {
                Q.push(it);
                dist[0][it]=1+dist[0][nod];
            }
        }
    }
    dist[1][N]=1;
    Q.push(N);
    while(!Q.empty())
    {
        int nod=Q.front();Q.pop();
        for(auto it:G[nod])
        {
            if(!dist[1][it])
            {
                Q.push(it);
                dist[1][it]=1+dist[1][nod];
            }
        }
    }
    for(int i=1;i<=N;i++)
    {
        if(dist[0][i]<=dist[1][i])
            szA++;
        else
            szB++;
    }
    if(szA<=szB)cout<<"Snuke";
    else        cout<<"Fennec";
    return 0;
}
