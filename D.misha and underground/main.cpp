#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int T[18][100005];
int lvl[100005];
vector<int> G[100005];
int N,Q;
int dfs(int nod,int tata,int nvl)
{
    lvl[nod]=nvl;
    for(auto it:G[nod])
        if(tata!=it)
            dfs(it,nod,nvl+1);
}
int lca(int x,int y)
{
    int pas=17;
    if(lvl[x]>lvl[y])swap(x,y);
    while(lvl[x]<lvl[y])
    {
        if((lvl[y]-lvl[x])>=(1<<pas))
        {
            y=T[pas][y];
        }
        pas--;
    }
    if(x==y)return x;
    pas=17;
    while(pas>=0)
    {
        if(T[pas][x]!=T[pas][y])
        {
            x=T[pas][x];
            y=T[pas][y];
        }
        pas--;
    }
    return T[0][x];
}
int tr(int s,int t,int f)
{
    int rez=0;
    int a,b,c;
    a=lca(s,t);
    b=lca(t,f);
    c=lca(s,f);
    rez+=min(lvl[f]-lvl[b]+1,lvl[f]-lvl[c]+1);
    if(lvl[a]>=lvl[c])
    {
        rez+=lvl[a]-lvl[c];
    }
    return rez;
}
int main()
{
    scanf("%d %d",&N,&Q);
    for(int i=2;i<=N;i++){scanf("%d",&T[0][i]);G[i].push_back(T[0][i]);G[T[0][i]].push_back(i);}
    for(int i=1;i<=17;i++)
    {
        for(int j=1;j<=N;j++)
            T[i][j]=T[i-1][T[i-1][j]];
    }
    dfs(1,0,1);
    for(int i=1;i<=Q;i++)
    {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        int rez=0;
        rez=max(rez,tr(a,b,c));
        rez=max(rez,tr(a,c,b));
        rez=max(rez,tr(b,a,c));
        rez=max(rez,tr(b,c,a));
        rez=max(rez,tr(c,a,b));
        rez=max(rez,tr(c,b,a));
        printf("%d\n",rez);
    }
    return 0;
}
