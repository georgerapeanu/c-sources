#include <cstdio>
using namespace std;
FILE *f=fopen("perechi.in","r");
FILE *g=fopen("perechi.out","w");
long long N;
long long P[1005];
long  E[1005];
long long nr=1,i,k;
int main()
{
    fscanf(f,"%lld",&N);
    for(i=2;i*i<=N;i++)
    {
        if(N%i==0)
        {
            P[++k]=i;
            E[k]=0;
            while(N%i==0)
            {
                E[k]++;
                N/=i;
            }
        }
    }
    if(N>1)
    {
        P[++k]=N;
        E[k]=1;
    }
    for(i=1;i<=k;i++)
        nr*=(2*E[i]+1);
    nr++;
    nr/=2;
    fprintf(g,"%lld",nr);
    fclose(f);
    fclose(g);
    return 0;
}
