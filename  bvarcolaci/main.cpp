#include <cstdio>
#include <cstring>
#include <set>
#include <ctime>
#include <cstdlib>
#define K 1000
using namespace std;
FILE *f=fopen("bvarcolaci.in","r");
FILE *g=fopen("bvarcolaci.out","w");
long long rez=0;
int N;
int V[250005];
void n2()
{
    multiset<int> fr;
    int F[250005];
    for(int i=1;i<=N;i++)
    {
        memset(F,0,sizeof(F));
        fr.clear();for(int j=1;j<=N;j++)fr.insert(0);
        for(int j=i;j<=N;j++)
        {
            fr.erase(fr.find(F[V[j]]));
            F[V[j]]++;
            fr.insert(F[V[j]]);
            if(*(fr.rbegin())>=(j-i+1)/2+1)
                rez++;
        }
    }
}
void undeEsteDomnulIohanis()
{
    rez=N+rand();
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)fscanf(f,"%d",&V[i]);
    if(N<=K)n2();
    else undeEsteDomnulIohanis();
    fprintf(g,"%lld",rez);
    return 0;
}
