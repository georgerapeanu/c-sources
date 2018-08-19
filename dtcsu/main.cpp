#include <cstdio>
#include <vector>
#include <algorithm>
#define LEN 4096
#define MOD 12034
using namespace std;
FILE *f;
FILE *g=fopen("dtcsu.out","w");
int rez;
long long Q,val;
vector<long long> H[MOD+1];
int main()
{
    f=fopen("dtcsu.in","r");
    for(int i=1;i<=276997;i++)
    {
        fscanf(f,"%lld",&val);
        if(val%2==1)
            H[val%MOD].push_back(val);
    }
    fscanf(f,"%lld",&Q);
    for(int i=1;i<=Q;i++)
    {
        fscanf(f,"%lld",&val);
        if(!val) continue;
        val=val/(val&(-val));
        if(find(H[val%MOD].begin(),H[val%MOD].end(),val)!=H[val%MOD].end())
            rez++;
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
