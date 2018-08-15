#include <iostream>
#include <cstdlib>
#include <vector>
#include <bitset>
using namespace std;
vector<int> V[100005];
int N;
int C[100005];
int cul[100005];
bitset<100005> viz;
void df2(int nod)
{
    viz[nod]=1;
    cul[nod]=C[nod];
    for(auto it:V[nod])
    {
        if(viz[it]) continue;
        df2(it);
        if(cul[it]!=cul[nod])
            cul[nod]=-1;
    }
}
int dfs(int nod,int culo)
{
    viz[nod]=1;
    int elim=0;
    int nr=0;
    bool ok=0;
    for(auto it:V[nod])
    {
        if(viz[it]) continue;
        if(cul[it]==-1)
        {
            nr++;elim=it;
        }
        else if(C[nod]!=cul[it])
            ok=1;
    }
    ok|=(culo!=C[nod]);
    if(nr==0) {cout<<"YES\n"<<nod;exit(0);}
    if(nr==1)
    {
        if(ok)
            return -1;
        dfs(elim,culo);
    }
    else
    {
        return -1;
    }
}
int main()
{
    cin>>N;
    for(int i=1;i<N;i++)
    {
        int x,y;
        cin>>x>>y;
        V[x].push_back(y);
        V[y].push_back(x);
    }
    for(int i=1;i<=N;i++)
        cin>>C[i];
    df2(1);viz.reset();
    dfs(1,C[1]);
    cout<<"NO\n";
    return 0;
}
