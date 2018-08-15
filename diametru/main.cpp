#include <iostream>
#include <cstdio>
#include <queue>
#include <set>
#include <cstring>
#include <vector>
using namespace std;
int dist[105];
int N,M;
vector<int> G[100];
int corect()
{
    int rez=0;
    for(int i=1;i<=N;i++)
    {
        queue<int> Q;
        Q.push(i);
        memset(dist,0,sizeof(dist));
        dist[i]=1;
        while(!Q.empty())
        {
            int nod=Q.front();Q.pop();
            rez=max(rez,dist[nod]);
            for(auto it:G[nod])
            {
                if(!dist[it]){dist[it]=dist[nod]+1;Q.push(it);}
            }
        }
    }
    return rez;
}
int gigel()
{
    int nod=1;
    int rez=0,K=0;
    set<pair<int,int> > S;
    int wut=corect();
    while(wut!=rez)
    {
        queue<int> Q;
        memset(dist,0,sizeof(dist));
        Q.push(nod);
        dist[nod]=1;
        int tmp=0;
        while(!Q.empty())
        {
            int nod=Q.front();Q.pop();
            rez=max(rez,dist[nod]);
            tmp=max(tmp,dist[nod]);
            for(auto it:G[nod])
            {
                if(!dist[it]){dist[it]=dist[nod]+1;Q.push(it);}
            }
        }
        int nxt=0;
        for(int i=1;i<=N;i++)
        {
            if(tmp==dist[i]&&S.find(make_pair(nod,i))==S.end())
            {
                nxt=i;
                break;
            }
        }
        if(!nxt)for(int i=1;i<=N;i++)if(tmp==dist[i]){nxt=i;break;}
        S.insert(make_pair(nod,nxt));
        S.insert(make_pair(nxt,nod));
        nod=nxt;
        K++;
    }
    return K;
}
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    cin>>N>>M;
    for(int i=1;i<=M;i++)
    {
        int x,y;
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    cout<<gigel();
    return 0;
}
