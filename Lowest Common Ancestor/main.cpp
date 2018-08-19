#include <cstdio>
#include <vector>
#include <bitset>
#define MAXL 21
#define MAXN 100005
using namespace std;
FILE *f=fopen("lca.in","r");
FILE *g=fopen("lca.out","w");
int T[MAXL][MAXN];
int nvl[MAXN],N,maxlvl,M;
///bitset<MAXN> B;
vector <int> V[MAXN];
void dfs(int nod,int nivel)
{
    ///B[nod]=1;
    nvl[nod]=nivel;
    maxlvl=max(maxlvl,nivel);
    for(auto it:V[nod])
       /// if(!B[it])
            dfs(it,nivel+1);
}
int lca(int x,int y)
{
    if(nvl[x]<nvl[y])
        swap(x,y);
    int dif=nvl[x]-nvl[y],str=0;
    while(dif)
    {
        if(dif&1)
            x=T[str][x];
        dif>>=1;
        str++;
    }
    if(x==y)
        return x;
    for(int i=MAXL-1;i>=0;i--)
        if(T[i][x]&&T[i][x]!=T[i][y])
            x=T[i][x],y=T[i][y];
    return T[0][x];
}
void read()
{
    fscanf(f,"%d%d",&N,&M);
    for(int i=2;i<=N;i++)
    {
        fscanf(f,"%d",&T[0][i]);
        V[T[0][i]].push_back(i);
    }
        dfs(1,1);
    for(int i=1;(1<<i)<=maxlvl;i++)
        for(int j=1;j<=N;j++)
            T[i][j]=T[i-1][T[i-1][j]];
}

int main()
{
    read();
    for(int i=1;i<=M;i++)
    {
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        fprintf(g,"%d\n",lca(x,y));
    }
    fclose(f);
    fclose(g);
    return 0;
}
