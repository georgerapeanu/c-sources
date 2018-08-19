#include <iostream>
#include <vector>
#include <bitset>
#define inf 1<<30
using namespace std;
vector <pair<int,int> > V[101];
int D[101][100],N,Q,x,y,val;
bitset <101> viz;
int dfs(int nod)
{
    int sumnod=0,f1=0,f2=0,w1,w2;
    viz[nod]=1;
    for(auto it:V[nod])
    {
        if(viz[(it).first])
        {
            sumnod=(it).second;
        }
        else
        {
            if(!f1)
                {f1=it.first;w1=dfs(it.first);}
            else
                {f2=it.first;w2=dfs(it.first);}
        }
    }
    if(!f1)
    {
        D[nod][1]=sumnod;
        return 1;
    }
    else if(!f2)
    {
        for(int i=0;i<=w1;i++)
        {
            D[nod][i]=D[f1][i];
        }
        D[nod][1+w1]=D[f1][w1]+sumnod;
        return 1+w1;
    }
    else
    {
        for(int i=0;i<=w1+w2;i++)
        {
            D[nod][i]=inf;
            for(int x=max(0,i-w2);x<=w1&&x<=i;x++)
            {
                D[nod][i]=min(D[nod][i],D[f1][x]+D[f2][i-x]);
            }
        }
        D[nod][1+w1+w2]=D[f1][w1]+D[f2][w2]+sumnod;
        return 1+w1+w2;
    }
}
int main()
{
    cin>>N>>Q;
    for(int i=1;i<N;i++)
    {
        cin>>x>>y>>val;
        V[x].push_back(make_pair(y,val));
        V[y].push_back(make_pair(x,val));
    }
    dfs(1);
    cout<<D[1][N-1]-D[1][N-1-Q];
    return 0;
}
