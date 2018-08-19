#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
FILE *f=fopen("parb2.in","r");
FILE *g=fopen("parb2.out","w");
vector<pair<int,char> > G[100005];
int lvl[100005];
int pos[100005];
int tmp[100005];
int ceva[17][100005];
int sa[100005];
int T[17][100005];
int len=0;
int gap,N,Q;
void dfs(int nod,int tata)
{
    T[0][nod]=tata;
    lvl[nod]=lvl[tata]+1;
    for(auto it:G[nod])
    {
        if(tata==it.first)continue;
        sa[++len]=it.first;
        pos[it.first]=it.second-'a';
        dfs(it.first,nod);
    }
}
bool cmp(int i,int j)
{
    if(pos[i]!=pos[j])return pos[i]<pos[j];
    if(!T[gap][i]||!T[gap][j])return lvl[i]<lvl[j];
    i=T[gap][i];
    j=T[gap][j];
    return pos[i]<pos[j];
}
void compT()
{
    for(int i=1;i<17;i++)
    {
        for(int j=1;j<=N;j++)
        {
            T[i][j]=T[i-1][T[i-1][j]];
        }
    }
}
void build()
{
    for(gap=0;(1<<gap)<N;gap++)
    {
        for(int i=1;i<=N;i++)ceva[gap][i]=pos[i];
        sort(sa+1,sa+N,cmp);
        for(int i=1;i<N-1;i++)tmp[i+1]=tmp[i]+cmp(sa[i],sa[i+1]);
        for(int i=1;i<N;i++)pos[sa[i]]=tmp[i];
    }
    for(int i=1;i<=N;i++)ceva[gap][sa[i]]=pos[i];
    for(int i=1;i<=N-1;i++)pos[sa[i]]=i;
}
int lcp(int a,int b)
{
    int rez=0;
    for(int pas=16;pas>=0;pas--)
    {
        if(T[pas][a]&&T[pas][b])
        {
            if(ceva[pas][a]==ceva[pas][b])
            {
                rez+=(1<<pas);
                a=T[pas][a];
                b=T[pas][b];
            }
        }
    }
    return rez;
}
int query(int x,int y)
{
    int len=lvl[y]-lvl[x];
    int l,r;
    int st,dr;
    st=0;dr=pos[y];
    while(dr-st>1)
    {
        int mid=(st+dr)/2;
        if(lcp(sa[mid],sa[pos[y]])>=len)
            dr=mid;
        else
            st=mid;
    }
    l=dr;
    st=pos[y];
    dr=N-1;
    while(dr-st>1)
    {
        int mid=(st+dr)/2;
        if(lcp(sa[mid],sa[pos[y]])>=len)
            st=mid;
        else
            dr=mid;
    }
    r=st;
    return r-l+1;
}
int main()
{
    fscanf(f,"%d %d\n",&N,&Q);
    for(int i=1;i<N;i++)
    {
        int x,y;
        char c;
        fscanf(f,"%d %d %c\n",&x,&y,&c);
        G[x].push_back({y,c});
        G[y].push_back({x,c});
    }
    dfs(1,0);
    compT();
    build();
    while(Q--)
    {
        int x,y;
        fscanf(f,"%d %d\n",&x,&y);
        fprintf(g,"%d\n",query(x,y));
    }
    fclose(f);
    fclose(g);
    return 0;
}
