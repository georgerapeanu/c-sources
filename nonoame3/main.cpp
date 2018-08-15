#include <cstdio>
using namespace std;
FILE *f=fopen("noname3.in","r");
FILE *g=fopen("noname3.out","w");
long long S,N,K,V[1000005],i;
int main()
{
    fscanf(f,"%lld%lld",&N,&S);
    K=((S-((N-1)*N/2))-(N-1)-1)/N;
    for(i=1;i<N;i++)
        V[i]=i+K;
    V[N]=S-((N-1)*N/2)-K*(N-1);
    if(V[N-1]<V[N]-2)
    {
        V[N-1]++;
        V[N]--;
        i=N-2;
        while(V[N]-1>V[N-1])
        {
            V[N]--;
            V[i]++;
            i--;
        }
    }
    for(i=1;i<=N;i++)
        fprintf(g,"%lld ",V[i]);
    fclose(f);
    fclose(g);
    return 0;
}
