#include <cstdio>
#include <algorithm>
#include <bitset>
#include <vector>
using namespace std;
FILE *f=fopen("ctc.in","r");
FILE *g=fopen("ctc.out","w");
int id[100005],len;
vector <int> G[100005];
vector<vector<int> > compo;
int low[100005];
int st[100005];
bool inst[100005];
int i,N,M,x,y,nr;
int lastid;
void tarjan(int nod)
{
    id[nod]=low[nod]=++lastid;
    st[++len]=nod;inst[nod]=1;
    for(auto it:G[nod])
    {
        if(!id[it])tarjan(it);
        if(inst[it])low[nod]=min(low[nod],low[it]);
    }
    if(low[nod]==id[nod])
    {
        vector<int> V;
        while(st[len]!=nod)
        {
            V.push_back(st[len]);
            inst[st[len]]=0;
            len--;
        }
        V.push_back(st[len]);
        inst[st[len]]=0;
        len--;
        compo.push_back(V);
    }
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%d %d",&x,&y);
        G[x].push_back(y);
    }
    for(int i=1;i<=N;i++)if(!id[i])tarjan(i);
    fprintf(g,"%d\n",compo.size());
    for(auto i:compo)
    {
        for(auto it:i)
            fprintf(g,"%d ",it);
        fprintf(g,"\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
