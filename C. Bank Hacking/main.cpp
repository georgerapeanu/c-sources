#include <iostream>
#include <bitset>
#include <queue>
#include <set>
#define mp make_pair
using namespace std;
set <pair<int,int> > H;
bitset<300005> B;
bitset<300005> tmp;
int V[300005];
int N;
int rez=(-(1<<30));
vector<int> G[300005];
void bfs(int nod,int maxdist)
{
    queue<pair<int,int> >Q;
    Q.push(make_pair(nod,0));
    tmp.reset();tmp[nod]=1;
    while(!Q.empty())
    {
        if(Q.front().second>maxdist){Q.pop();continue;}
        V[Q.front().first]++;
        H.erase(mp(V[Q.front().first]-1,Q.front().first));
        H.insert(mp(V[Q.front().first],Q.front().first));
        for(auto it:G[Q.front().first])
        {
            if(!tmp[it]&&!B[it]){tmp[it]=1;Q.push(make_pair(it,Q.front().second+1));}
        }
        Q.pop();
    }
}
int main()
{
    cin>>N;
    V[0]=rez;
    int maxim=0;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i];
        if(V[i]>V[maxim])
            maxim=i;
    }
    for(int i=1;i<N;i++)
    {
        int st,dr;
        cin>>st>>dr;
        G[st].push_back(dr);
        G[dr].push_back(st);
    }
    H.insert(mp(V[maxim],maxim));
    while(!H.empty())
    {
        rez=max(H.rbegin()->first,rez);
        bfs(H.rbegin()->second,2);
        for(auto it:G[H.rbegin()->second])
            if(!B[it]) H.insert(mp(V[it],it));
        B[H.rbegin()->second]=1;
        H.erase(*H.rbegin());
    }
    cout<<rez;
    return 0;
}
