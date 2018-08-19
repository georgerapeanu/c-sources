#include <cstdio>
#include <algorithm>
#define poz(x) ((x-1)%K+1)
using namespace std;
FILE *f=fopen("lss.in","r");
FILE *g=fopen("lss.out","w");
int N,K;
int V[100005];
long long rez;
int main()
{
    fscanf(f,"%d%d",&K,&N);
    for(int i=1;i<=N;i++) fscanf(f,"%d",&V[i]);
    sort(V+1,V+1+N);
    for(int i=1;i<=N;i++)
        rez+=max(1,poz(V[i])-i+1);
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
