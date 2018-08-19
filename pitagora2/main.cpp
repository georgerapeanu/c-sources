#include <cstdio>
using namespace std;
FILE *f=fopen("pitagora2.in","r");
FILE *g=fopen("pitagora2.out","w");
long long N;
long long i,B,C,rez=250000000,D[50000],j;
int main()
{
    fscanf(f,"%lld",&N);
    for(i=1;i*i<=N;i++)
    {
        if(N%i==0)
        {
            D[++D[0]]=i;
            D[++D[0]]=N/i;
        }
    }
    for(i=1;i<=D[0];i++)
    {
        for(j=1;j<=D[0];j++)
        {
            if(D[i]*D[j]<=N&&((N/D[i])*(N/D[j])+D[i]*D[j])%2==0)
            {
                C=((N/D[i])*(N/D[j])+D[i]*D[j])/2;
                B=C-D[i]*D[j];
                if(B<rez&&B)
                    rez=B;
            }
        }
    }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
