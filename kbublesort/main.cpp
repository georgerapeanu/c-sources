#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("kbubblesort.in","r");
FILE *g=fopen("kbubblesort.out","w");
bool ok;
int v[1000050];
int N,aux;
long long K,nr,i;
int main()
{
    fscanf(f,"%d%lld",&N,&K);
    for(i=1;i<=N;i++)
        fscanf(f,"%d",&v[i]);
    ok = 1;
    while(ok&&nr<K)
    {
        ok = 0;
        for(i = 1; i < N&&nr<K; i++)
            if(v[i] > v[i + 1])
            {
                aux=v[i];
                v[i]=v[i+1];
                v[i+1]=aux;
                ok = 1;
                nr++;
            }
    }
    for(i=1;i<=N;i++)
        fprintf(g,"%d ",v[i]);
    fclose(f);
    fclose(g);
    return 0;
}
