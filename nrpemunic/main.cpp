#include <cstdio>
#include <cmath>
using namespace std;
FILE *f=fopen("npermunic.in","r");
FILE *g=fopen("npermunic.out","w");
long long frecv[25],i,N,a,j,rez=1,factorial[25],n,b,c;
long long facto(int N)
{
    if(N==1)
        return 1;
    if(factorial[N])
        return factorial[N];
    factorial[N]=facto(N-1)*N;
    return factorial[N];
}
int main()
{
    fscanf(f,"%lld",&N);
    factorial[0]=factorial[1]=1;
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%lld",&a);
        frecv[a]++;
    }
    n=N;
    for(i=1;i<=n-1;i++)
    {
        a=facto(N);
        b=facto(frecv[i]);
        c=facto(N-frecv[i]);
        rez=rez*a/(b*c);
        N-=frecv[i];
    }
    fprintf(g,"%lld",rez);
    return 0;
}
