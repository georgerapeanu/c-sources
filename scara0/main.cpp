#include <cstdio>
using namespace std;
FILE *f=fopen("scara.in","r");
FILE *g=fopen("scara.out","w");
long long V[10000000],nr,N,K,nr0,i,fost,a;
int main()
{
    fscanf(f,"%lld %lld",&N,&K);
    fclose(f);
    V[0]=1;
    V[1]=1;
    nr0=1;
    fost=1;
    for(nr=2;nr<=N+1;nr++)
    {
        nr0++;
        if(nr0==K+1)
            nr0=1;
        if(nr0==1)
        {
            a=V[nr0];
            V[nr0]=(V[K]*2-fost)%1999999973;
        }
        else
        {
            a=V[nr0];
            V[nr0]=(V[nr0-1]*2-fost)%1999999973;
        }
        fost=a;
    }
        if(V[nr0]<0)
            V[nr0]+=1999999973;
        fprintf(g,"%lld",V[nr0]);
    return 0;
}
