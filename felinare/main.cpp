#include <cstdio>
#include <vector>
#include <bitset>
using namespace std;
FILE *f=fopen("felinare.in","r");
FILE *g=fopen("felinare.out","w");
vector<int> G[8200];
int L[8200],R[8200];
bitset<8200> U;
bool sl[8200];
bool sr[8200];
int N,M;
int x,y;
int nr=0;
int pairup(int nod)
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
            R[it]=nod;
            L[nod]=it;
            return 1;
        }
    }
    return 0;
}
void suport(int nod)
{
    for(auto it:G[nod])
    {
        if(!sr[it])
        {
            sr[it]=1;
            sl[R[it]]=0;
            suport(R[it]);
        }
    }
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d %d",&x,&y);
        G[x].push_back(y);
    }
    bool ok=1;
    while(ok)
    {
        ok=0;
        U.reset();
        for(int i=1;i<=N;i++)
        {
            if(!L[i])
            {
                if(pairup(i))
                {
                    nr++;
                    ok=1;
                }
            }
        }
    }
    for(int i=1;i<=N;i++)if(L[i])sl[i]=1;
    for(int i=1;i<=N;i++)
    {
        if(!sl[i])suport(i);
    }
    fprintf(g,"%d\n",2*N-nr);
    for(int i=1;i<=N;i++)
    {
        fprintf(g,"%d\n",((!sr[i])<<1)+(!sl[i]));
    }
    fclose(f);
    fclose(g);
    return 0;
}
