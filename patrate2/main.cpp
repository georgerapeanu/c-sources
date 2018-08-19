#include <cstdio>
#define baza 1000000
using namespace std;
FILE *f=fopen("patrate2.in","r");
FILE *g=fopen("patrate2.out","w");
long long A[4000];
long long N,i;
void shr(long long V[])
{
    for(long long i=V[0]+1;i>0;i--)
        V[i]=V[i-1];
    V[1]=0;
    V[0]++;
}
void inm(long long V[],long long nr)
{
    for(long long i=1;i<=V[0];i++)
        V[i]*=nr;
    for(long long i=V[0];i>1;i--)
    {
        V[i-1]+=V[i]/baza;
        V[i]%=baza;
    }
    while(V[1]>=baza)
    {
        shr(V);
        V[1]=V[2]/baza;
        V[2]%=baza;
    }
}
int main()
{
    fscanf(f,"%lld",&N);
    A[0]=A[1]=1;
    for(i=2;i<=N;i++)
    {
        inm(A,i);
    }
    N=N*N;
    for(i=1;i<=N;i++)
        inm(A,2);
    for(i=1;i<=A[0];i++)
    {
        if(i!=1)
        {
            if(A[i]>=100000)
                fprintf(g,"%lld",A[i]);
            else if(A[i]>=10000)
                fprintf(g,"0%lld",A[i]);
            else if(A[i]>=1000)
                fprintf(g,"00%lld",A[i]);
            else if(A[i]>=100)
                fprintf(g,"000%lld",A[i]);
            else if(A[i]>=10)
                fprintf(g,"0000%lld",A[i]);
            else if(A[i]>=1)
                fprintf(g,"00000%lld",A[i]);
            else
                fprintf(g,"000000");
        }
        else
            fprintf(g,"%lld",A[i]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
