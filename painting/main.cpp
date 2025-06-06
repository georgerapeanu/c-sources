#include <cstdio>
#include <vector>
#include <bitset>
using namespace std;
FILE *f=fopen("painting.in","r");
FILE *g=fopen("painting.out","w");
vector<int> V[100005];
vector<int> arb[100005];
int N,M,x,y;
int i;
int cul[100005];
bitset <100005> U;
vector<pair<int,int> >v;
void dfs(int nod,int t)
{
    cul[nod]=1;
    for(auto it:V[nod])
    {
        if(it!=t)
        {
            dfs(it,nod);
            arb[nod].push_back(it);
        }
    }
}
void color(int nod,int col)
{
    if(U[nod])
        return ;
    U[nod]=1;
    cul[nod]=col;
    for(auto it:arb[nod])
        color(it,col);
}
int main()
{
    fscanf(f,"%d%d",&N,&M);
    for(i=1;i<N;i++)
    {
        fscanf(f,"%d %d",&x,&y);
        V[x].push_back(y);
        V[y].push_back(x);
    }
    dfs(1,0);
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%d %d",&x,&y);
        v.push_back(make_pair(x,y));
    }
    for(vector<pair<int,int> >::reverse_iterator it=v.rbegin();it!=v.rend();it++)
        color((*it).first,(*it).second);
    for(i=1;i<=N;i++)
        fprintf(g,"%d ",cul[i]);
    fclose(f);
    fclose(g);
    return 0;
}
