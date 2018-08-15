#include <cstdio>
#include <vector>
#define NMAX 100001
using namespace std;
FILE *f=fopen("maimute.in","r");
FILE *g=fopen("maimute.out","w");
int first[NMAX],last[NMAX];
int len;
int N,M,x,y;
vector<int> V[NMAX];
void dfs(int nod,int tata,int nivel)
{
    first[nod]=++len;
    last[nod]=len;
    for(auto it:V[nod])
    {
        if(it!=tata)
            dfs(it,nod,nivel+1);
        last[nod]=++len;
    }
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<N;i++)
    {
        fscanf(f,"%d%d",&x,&y);
        V[x].push_back(y);
        V[y].push_back(x);
    }
    dfs(1,0,0);
    fscanf(f,"%d",&M);
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d%d",&x,&y);
        if((first[x]<first[y]&&last[x]>last[y])||(first[x]>first[y]&&last[x]<last[y])) fputs("DA\n",g);
        else fputs("NU\n",g);
    }
    fclose(f);
    fclose(g);
    return 0;
}
