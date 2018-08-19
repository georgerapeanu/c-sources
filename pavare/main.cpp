#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("pavare.in","r");
FILE *g=fopen("pavare.out","w");
long long N,rez,dif;
int V[80000];
int c;
long long dist(long long x)
{
    if(x%2==0)
    {
        return (x*x+2*x)/4;
    }
    return (x*x+2*x+1)/4;
}
int main()
{
    fscanf(f,"%d%lld",&c,&N);
    rez=2*sqrt(N);
    if(dist(rez-1)>=N)
        rez--;
    if(c==1)
    {
        fprintf(g,"%lld",rez);
        return 0;
    }
    dif=dist(rez)-N;
    for(int i=1;i<=rez/2+rez%2;i++)
        V[i]=V[rez-i+1]=i;
    while(dif)
    {
        for(int i=rez/2+rez%2;i>0&&dif>0;i--)
        {
            V[i]--;
            dif--;
        }
    }
    for(long long i=1;i<=rez;i++)
        fprintf(g,"%d ",V[i]);
    fclose(f);
    fclose(g);
    return 0;
}
