#include <iostream>
#include <bitset>
#include <vector>
#include <queue>
using namespace std;
int N,M;
vector<int> G[100005];
priority_queue<int> H;
int V[100005];
int val;
int gr[100005];
bitset<100005> viz;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N>>M;
    for(int i=1;i<=M;i++)
    {
        int x,y;
        cin>>x>>y;
        G[y].push_back(x);
        gr[x]++;
    }
    for(int i=1;i<=N;i++)
        if(gr[i]==0)
            H.push(i);
    for(int i=N;i;i--)
    {
        int nod=H.top();H.pop();
        V[nod]=i;
        for(auto it:G[nod])
        {
            gr[it]--;
            if(!gr[it])
                H.push(it);
        }
    }
    for(int i=1;i<=N;i++)
        cout<<V[i]<<" ";
    return 0;
}
