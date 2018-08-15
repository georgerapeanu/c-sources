#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("palma.in","r");
FILE *g=fopen("palma.out","w");
long long V[250005];
long long N,H,i,val,j;
long long S,K[505];
int main()
{
    fscanf(f,"%lld %lld %lld",&N,&H,&S);
    for(i=1;i<=N;i++)
        fscanf(f,"%lld",&K[i]);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=H;j++)
        {
            fscanf(f,"%lld",&val);
            if(val<K[i])
                V[++V[0]]=val;
        }
    }
    sort(V+1,V+1+V[0]);
    i=1;
    while(S>=V[i]&&i<=V[0])
    {S-=V[i];i++;}
    fprintf(g,"%lld",i-1);
    fclose(f);
    fclose(g);
    return 0;
}
