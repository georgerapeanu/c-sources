#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("caluti.in","r");
FILE *g=fopen("caluti.out","w");
long long best[100005],K,N,T,X,P,j,i;
int main()
{
    fscanf(f,"%lld",&T);
    for(i=1;i<=T;i++)
    {
        fscanf(f,"%lld %lld %lld",&N,&K,&P);
        for(j=1;j<=N;j++)
        {
            fscanf(f,"%lld",&X);
            best[j]=max(best[max(0LL,j-K)],X)+P;
        }
        fprintf(g,"%lld\n",best[N]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
