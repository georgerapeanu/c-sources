#include <cstdio>
#include <set>
#define LL long long
using namespace std;
FILE *f=fopen("divseq.in","r");
FILE *g=fopen("divseq.out","w");
LL rez;
int N;
LL V[250001];
multiset<LL> S;
multiset<LL>::iterator it;
bool ok(LL val)
{
    if(S.find(val)!=S.end())
        return 1;
    it=S.lower_bound(val);
    if(it!=S.end()&&(*it)%val)
        return 0;
    if(it!=S.begin())
    {
        it--;
        if(val%(*it)!=0)
            return 0;
    }
    return 1;
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%lld",&V[i]);
    }
    int dr=0;
    for(int st=1;st<=N;st++)
    {
        dr=max(dr,st-1);
        while(dr<N&&ok(V[dr+1]))
        {
            dr++;
            S.insert(V[dr]);
        }
        rez+=dr-st+1;
        S.erase(S.find(V[st]));
    }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
