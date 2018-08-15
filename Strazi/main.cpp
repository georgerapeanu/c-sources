#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
FILE *f=fopen("strazi.in","r");
FILE *g=fopen("strazi.out","w");
int L[300],N,M;
int R[300];
int tmp[300];
bool U[300];
vector<int> G[300];
vector<int> rez;
bool pairup(int nod)
{
    if(U[nod])return 0;
    U[nod]=1;
    for(auto it:G[nod])
    {
        if(!R[it])
        {
            R[it]=nod;
            L[nod]=it;
            return 1;
        }
    }
    for(auto it:G[nod])
    {
        if(pairup(R[it]))
        {
            R[it]=nod;
            L[nod]=it;
            return 1;
        }
    }
    return 0;
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(int i=1;i<=M;i++)
    {
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        G[x].push_back(y);
    }
    int c=0;
    bool ok=1;
    while(ok)
    {
        ok=0;
        memset(U,0,sizeof(U));
        for(int i=1;i<=N;i++)
        {
            if(!L[i]&&pairup(i))
            {
                c++;
                ok=1;
            }
        }
    }
    fprintf(g,"%d\n",N-1-c);
    memset(U,0,sizeof(U));
    for(int i=1;i<=N;i++)tmp[L[i]]=i;
    for(int i=1;i<=N;i++)
    {
        if(U[i])continue;
        int fst;
        for(fst=i;tmp[fst];fst=tmp[fst]);
        if(rez.size())fprintf(g,"%d %d\n",rez.back(),fst);
        for(int nod=fst;nod;nod=L[nod])
        {
            U[nod]=1;
            rez.push_back(nod);
        }
    }
    for(auto it:rez)fprintf(g,"%d ",it);
    fclose(f);
    fclose(g);
    return 0;
}
