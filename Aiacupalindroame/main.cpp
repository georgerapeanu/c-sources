#include <cstdio>
#include <vector>
#define MOD1 666013
#define MOD2 123456
#define NMAX 100005
using namespace std;
FILE *f=fopen("aiacupalindroame.in","r");
FILE *g=fopen("aiacupalindroame.out","w");
int h1[NMAX];
int h2[NMAX];
char C[NMAX];
int lvl[NMAX];
vector<int> G[NMAX];
int N,Q,val;
int l,r;
void dfs(int nod,int nvl,int H1,int H2)
{
    h1[nod]=H1;h2[nod]=H2;lvl[nod]=nvl;
    for(auto it:G[nod])
        dfs(it,nvl+1,(H1*26+C[it]-'a')%MOD1,(H2*26+C[it]-'a')%MOD2);
}
int main()
{
    fscanf(f,"%d %d\n",&N,&Q);
    for(int i=2;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        G[val].push_back(i);
    }
    fscanf(f,"\n");
    fgets(C+2,NMAX,f);
    dfs(1,1,0,0);
    for(int i=1;i<=Q;i++)
    {
        fscanf(f,"%d %d",&l,&r);
        fprintf(g,"%d\n",(h1[l]==h1[r]&&h2[l]==h2[r]&&lvl[l]==lvl[r]));
    }
    fclose(f);
    fclose(g);
    return 0;
}
