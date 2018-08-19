#include <cstdio>
#include <cstring>
#include <vector>
#include <bitset>
using namespace std;
FILE *f=fopen("fantasy.in","r");
FILE *g=fopen("fantasy.out","w");
int N,D,C,V,T;
int cod[1005];
vector<int> G[1005];
bitset<1005> viz;
int lvl[1005];
void dfs(int nod,int nvl)
{
    viz[nod]=1;
    lvl[nod]=nvl;
    for(auto it:G[nod])
    {
        if(!viz[it])
        {
            dfs(it,nvl+1);
            cod[nod]|=cod[it];
        }
    }
}
int main()
{
    fscanf(f,"%d",&T);
    while(T--)
    {
        fscanf(f,"%d%d%d%d",&N,&D,&C,&V);
        for(int i=1;i<=N;i++) G[i].clear();
        for(int i=1;i<N;i++)
        {
            int x,y;
            fscanf(f,"%d %d",&x,&y);
            G[x].push_back(y);
            G[y].push_back(x);
            memset(cod,0,sizeof(cod));
            viz.reset();
        }
        cod[D]=1;
        cod[C]=2;
        dfs(V,1);
        bool ok=0;
        for(int i=1;i<=N&&G[V].size()>2;i++)
            if(cod[i]!=3&&lvl[i]-1<lvl[C]-lvl[i]&&lvl[C]-lvl[i]<=lvl[D]+lvl[i]-1)
            {fputs("DA\n",g);ok=1;break;}
        if(ok) continue;
        for(auto it:G[V])
            ok|=(cod[it]==3||cod[it]==0);
        if(lvl[C]<=lvl[D]&&ok)  fputs("DA\n",g);
        else    fputs("NU\n",g);
    }
    fclose(f);
    fclose(g);
    return 0;
}
