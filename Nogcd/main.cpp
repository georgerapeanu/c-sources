#include <cstdio>
#include <vector>
#include <map>
using namespace std;
FILE *f=fopen("nogcd.in","r");
FILE *g=fopen("nogcd.out","w");
int N,M;
vector<int> G[100005];
bool viz[100005];
map<pair<int,int>,int> edges;
void dfs(int nod,int &lastval)
{
    viz[nod]=1;
    for(auto it:G[nod])
    {
        int a=nod,b=it;
        if(a>b)swap(a,b);
        if(edges.count({a,b}))continue;
        edges[{a,b}]=++lastval;
        if(!viz[it])dfs(it,lastval);
    }
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(int i=1;i<=M;i++)
    {
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    int val=0;
    dfs(1,val);
    for(auto it:edges)
        fprintf(g,"%d %d %d\n",it.first.first,it.first.second,it.second);
    fclose(f);
    fclose(g);
    return 0;
}
