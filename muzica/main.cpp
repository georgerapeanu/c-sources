#include <cstdio>
#include <algorithm>
#include <unordered_set>
#define MOD 25000
using namespace std;
FILE *f=fopen("muzica.in","r");
FILE *g=fopen("muzica.out","w");
int M,nr;
int C,D,E;
int N;
int val;
unordered_set<int> V[MOD];
int r1,r2,r3;
int main()
{
    fscanf(f,"%d %d",&N,&M);
    fscanf(f,"%d %d %d %d %d",&r1,&r2,&C,&D,&E);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        if(val!=r1&&val!=r2)
            V[val%MOD].insert(val);
        else
            nr++;
    }
    for(int i=3;i<=M;i++)
    {
        r3=(1LL*C*r2+1LL*D*r1)%E;
        int tmp=r3%MOD;
        if(find(V[tmp].begin(),V[tmp].end(),r3)!=V[tmp].end())
            {V[tmp].erase(r3);nr++;}
        r1=r2;
        r2=r3;
    }
    fprintf(g,"%d",nr);
    fclose(f);
    fclose(g);
    return 0;
}
