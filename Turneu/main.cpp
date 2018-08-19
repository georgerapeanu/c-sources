#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("turneu.in","r");
FILE *g=fopen("turneu.out","w");
int N;
int T;
double V[100005];
int main()
{
    fscanf(f,"%d",&T);
    while(T--)
    {
        fscanf(f,"%d",&N);
        for(int i=1;i<=N;i++)
        {
            fscanf(f,"%lf",&V[i]);
        }
        bool ok=1;
        for(int i=1;i<=N;i++)if(V[i]-(int)V[i]!=0&&V[i]-(int)V[i]!=0.5)ok=0;
        sort(V+1,V+1+N);
        ok&=(V[N]<N);
        for(int i=1;i<=N;i++)
        {
            V[i]+=V[i-1];
            ok&=(V[i]>=1LL*i*(i-1)/2);
        }
        ok&=(V[N]==1LL*N*(N-1)/2);
        fputs(ok ? "YES\n":"NO\n",g);
    }
    fclose(f);
    fclose(g);
    return 0;
}
