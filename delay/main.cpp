#include <cstdio>
#include <vector>
#define MAXL 15
#define MAXN 16005
#define zeros(x) x&(x^(x-1))
using namespace std;
FILE *f=fopen("delay.in","r");
FILE *g=fopen("delay.out","w");
int T[MAXL][MAXN],val[MAXN];
int nvl[MAXN],N,maxlvl,M;
vector <int> V[MAXN];
int AIB[2*MAXN];
int fpos[MAXN];
int lpos[MAXN];
int nrscv;
int query(int pos)
{
    int sum=0;
    for(int i=pos;i;i-=zeros(i))
        sum+=AIB[i];
    return sum;
}
void update(int pos,int val)
{
    for(int i=pos;i<=2*N;i+=zeros(i))
        AIB[i]+=val;
}
void linializare(int nod,int tata)
{
    nrscv++;
    fpos[nod]=nrscv;
    update(nrscv,val[nod]);
    for(auto it:V[nod])
        if(tata!=it)
            linializare(it,nod);
    nrscv++;
    lpos[nod]=nrscv;
    update(nrscv,-val[nod]);
}
void dfs(int nod,int nivel,int tata)
{
    nvl[nod]=nivel;
    maxlvl=max(maxlvl,nivel);
    for(auto it:V[nod])
    {
        if(it!=tata)
            dfs(it,nivel+1,nod),T[0][it]=nod;
    }
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
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val[i]);
    }
    for(int i=2;i<=N;i++)
    {
        int x,y;
        fscanf(f,"%d%d",&x,&y);
        V[x].push_back(y);
        V[y].push_back(x);
    }
    dfs(1,1,0);
    for(int i=1;(1<<i)<=maxlvl;i++)
        for(int j=1;j<=N;j++)
            T[i][j]=T[i-1][T[i-1][j]];
    linializare(1,0);
}

int main()
{
    read();
    fscanf(f,"%d",&M);
    for(int i=1;i<=M;i++)
    {
        int x,y,c;
        fscanf(f,"%d %d %d",&c,&x,&y);
        if(c==1)
        {
            update(fpos[x],y-val[x]);
            update(lpos[x],-y+val[x]);
            val[x]=y;
        }
        else
        {
            int nod=lca(x,y);
            fprintf(g,"%d\n",query(fpos[x])+query(fpos[y])-2*query(fpos[nod])+val[nod]);
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
