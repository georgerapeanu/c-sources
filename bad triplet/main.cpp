#include <iostream>
#include <cstdlib>
#include <set>
#include <vector>
#include <cassert>
using namespace std;
int st[100005];
bool viz[100005];
int lvl[100005];
vector<int> G[100005];
set<pair<int,int> > S;
int N,M;
void dfs(int nod,int tata)
{
    viz[nod]=1;
    st[++st[0]]=nod;
    lvl[nod]=st[0];
    for(auto it:G[nod])
    {
        if(viz[it]&&it!=tata)
        {
            if((lvl[nod]-lvl[it]+1)%3==0)
            {
                int d=(lvl[nod]-lvl[it]+1)/3;
                cout<<st[lvl[it]]<<" "<<st[lvl[it]+d]<<" "<<st[lvl[it]+2*d];
                assert(st[lvl[it]]!=st[lvl[it]+d]&&st[lvl[it]+d]!=st[lvl[it]+2*d]&&st[lvl[it]]!=st[lvl[it]+2*d]);
                assert(st[lvl[it]]);
                assert(st[lvl[it]+d]);
                assert(st[lvl[it]+2*d]);
                exit(0);
            }
        }
        if(!viz[it])
        {
            dfs(it,nod);
        }
    }
    st[0]--;
}
int main() {
    cin>>N>>M;
    for(int i=1;i<=M;i++){
        int x,y;
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
        S.insert({x,y});
        S.insert({y,x});
    }
    for(int i=1;i<=N;i++)
    {
        if(G[i].size()>2)
        {
            int x,y,z;
            x=G[i][0];
            y=G[i][1];
            z=G[i][2];
            assert(x);
            assert(y);
            assert(z);
            assert(i);
            if(S.count({x,y}))
            {
                cout<<i<<" "<<x<<" "<<y;
            }
            else if(S.count({x,z}))
            {
                cout<<i<<" "<<x<<" "<<z;
            }
            else if(S.count({y,z}))
            {
                cout<<i<<" "<<y<<" "<<z;
            }
            else
            {
                cout<<x<<" "<<y<<" "<<z;
            }
            return 0;
        }
    }
    dfs(1,0);
    cout<<-1;
    return 0;
}
