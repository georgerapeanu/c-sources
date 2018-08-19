#include <cstdio>
using namespace std;
FILE *f=fopen("sao.in","r");
FILE *g=fopen("sao.out","w");
long long A,S,a,b;
int minimcost=2000000000,N,M,i,cost;
int main()
{   fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%lld %lld",&a,&b);
        A+=a;
        S+=b;
    }
    fscanf(f,"%d",&M);
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%lld %lld %d",&a,&b,&cost);
        if(a>=A&&b>=S&&cost<minimcost)
            minimcost=cost;
    }
    fprintf(g,"%d",minimcost);
    fclose(f);
    fclose(g);
    return 0;
}
