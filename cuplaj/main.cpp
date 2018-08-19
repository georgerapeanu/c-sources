#include <cstdio>
#include <vector>
#include <bitset>
using namespace std;
FILE *f=fopen("cuplaj.in","r");
FILE *g=fopen("cuplaj.out","w");
int N,M,K;
vector<int> G[10005];
int L[10005];
int R[10005];
bitset<10005> U;
bool pairup(int nod)
{
    if(U[nod])return 0;
    U[nod]=1;
    for(auto it:G[nod])
    {
        if(!R[it])
        {
            L[nod]=it;
            R[it]=nod;
            return 1;
        }
    }
    for(auto it:G[nod])
    {
        if(pairup(R[it]))
        {
            L[nod]=it;
            R[it]=nod;
            return 1;
        }
    }
    return 0;
}
int main()
{
    fscanf(f,"%d%d%d",&N,&M,&K);
    for(int i=1;i<=K;i++)
    {
        int x,y;
        fscanf(f,"%d%d",&x,&y);
        G[x].push_back(y);
    }
    int c=0;
    bool ok=1;
    while(ok)
    {
        ok=0;
        U.reset();
        for(int i=1;i<=N;i++)
        {
            if(!L[i]&&pairup(i))
            {
                c++;
                ok=1;
            }
        }
    }
    fprintf(g,"%d\n",c);
    for(int i=1;i<=N;i++)
        if(L[i])
            fprintf(g,"%d %d\n",i,L[i]);
    fclose(f);
    fclose(g);
    return 0;
}
