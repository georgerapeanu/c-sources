#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
FILE *f=fopen("nivele2.in","r");
FILE *g=fopen("nivele2.out","w");
int N,viz[100005],i,j,u,v,maxnivel;
vector <int> V[100005];
vector <int> rez[100005];
void dfs(int nod,int pas)
{
    rez[pas].push_back(nod);
    maxnivel=max(maxnivel,pas);
    for(vector<int>::iterator it=V[nod].begin();it!=V[nod].end();it++)
        if(!viz[*it])
            {viz[*it]=1;dfs(*it,pas+1);}
}
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<N;i++)
    {
        fscanf(f,"%d %d",&u,&v);
        V[u].push_back(v);
        V[v].push_back(u);
    }
    viz[1]=1;
    dfs(1,1);
    for(i=1;i<=maxnivel;i++)
    {
        fprintf(g,"nivelul %d: ",i);
        for(vector <int> ::iterator it=rez[i].begin();it!=rez[i].end();it++)
            fprintf(g,"%d ",*it);
        fprintf(g,"\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
