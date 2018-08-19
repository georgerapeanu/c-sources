#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
bool R[500005];
int N,M,Q;
int x[500005];
int y[500005];
int w[500005];
int ind[500005];
int T[500005],last;
struct query
{
    int edge;
    int ind;
    int where;
    bool operator < (const query &other)const
    {
        if(w[edge]!=w[other.edge])return w[edge]<w[other.edge];
        return where<other.where;
    }
};
int len;
query V[500005];
vector<pair<int,int> > op;
int fi(int x,bool backup)
{
    if(!T[x])return x;
    if(backup)op.push_back({x,T[x]});
    return T[x]=fi(T[x],backup);
}
int u(int x,int y,bool backup)
{
    x=fi(x,backup);
    y=fi(y,backup);
    if(x==y)return 0;
    if(backup)op.push_back({x,0});
    T[x]=y;
    return 1;
}
bool cmp(int a,int b)
{
    return w[a]<w[b];
}
void rollback()
{
    while(!op.empty())
    {
        T[op.back().first]=op.back().second;
        op.pop_back();
    }
}
int main()
{
    scanf("%d %d",&N,&M);
    for(int i=1;i<=M;i++)
    {
        ind[i]=i;
        scanf("%d %d %d",&x[i],&y[i],&w[i]);
    }
    sort(ind+1,ind+1+M,cmp);
    scanf("%d",&Q);
    for(int i=1;i<=Q;i++)
    {
        query tmp;
        tmp.ind=0;tmp.where=i;
        int k;
        scanf("%d",&k);
        for(int j=0;j<k;j++)
        {
            int val;
            scanf("%d",&tmp.edge);
            V[++len]=tmp;
        }
    }
    sort(V+1,V+1+len);
    for(int i=1;i<=len;i++)
    {
        if(R[V[i].where])continue;
        while(w[ind[last+1]]<w[V[i].edge])
        {
            last++;
            u(x[ind[last]],y[ind[last]],0);
        }
        bool ok=u(x[V[i].edge],y[V[i].edge],1);
        while(V[i+1].where==V[i].where&&w[V[i].edge]==w[V[i+1].edge])
        {
            ok&=u(x[V[i+1].edge],y[V[i+1].edge],1);
            i++;
        }
        R[V[i].where]|=(!ok);
        rollback();
    }
    for(int i=1;i<=Q;i++)
        printf("%s\n",(R[i]==0 ? "YES":"NO"));
    return 0;
}
