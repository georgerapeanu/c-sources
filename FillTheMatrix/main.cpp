#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int T,N,q;
int P[100005];
vector<int> G[100005];
int viz[100005];
struct query
{
    int u,v,val;
}Q[1000005];
int fi(int x)
{
    if(P[x]<0)return x;
    return P[x]=fi(P[x]);
}
void u(int x,int y)
{
    x=fi(x);y=fi(y);
    if(y!=x)
    {
        P[y]+=P[x];
        P[x]=y;
    }
}
bool dfs(int nod,int tata,int lvl)
{
    viz[nod]=lvl;
    for(auto it:G[nod])
    {
        if(it!=tata)
        {
            if(viz[it])
            {
                if((viz[nod]-viz[it])%2==0)return 0;
            }
            else if(!dfs(it,nod,lvl+1))return 0;
        }
    }
    return 1;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&N,&q);
        for(int i=1;i<=N;i++)
        {
            viz[i]=0;P[i]=-1;G[i].clear();
        }
        for(int i=1;i<=q;i++)
        {
            scanf("%d %d %d",&Q[i].u,&Q[i].v,&Q[i].val);
            if(!Q[i].val)
            {
                u(Q[i].u,Q[i].v);
            }
        }
        bool ok=1;
        for(int i=1;i<=q;i++)
        {
            if(Q[i].val)
            {
                if(fi(Q[i].v)==fi(Q[i].u))
                {
                    printf("no\n");
                    ok=0;
                    break;
                }
                G[fi(Q[i].v)].push_back(fi(Q[i].u));
                G[fi(Q[i].u)].push_back(fi(Q[i].v));
            }
        }
        if(ok)
        {
            for(int i=1;i<=q;i++)
            {
                if(!viz[fi(Q[i].u)])
                {
                    ok&=dfs(fi(Q[i].u),0,1);
                }
                if(!viz[fi(Q[i].v)])
                {
                    ok&=dfs(fi(Q[i].v),0,1);
                }
            }
            printf(ok ? "yes\n":"no\n");
        }
    }
    return 0;
}
