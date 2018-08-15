#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("muzeu.in","r");
FILE *g=fopen("muzeu.out","w");
int d,i,N,K,a,b;
int main()
{
    fscanf(f,"%d%d",&N,&K);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d %d",&a,&b);
        d=max(d-min(a,d),0)+max(b-d,0);
    }
    fprintf(g,"%d",K-d);
    fclose(f);
    fclose(g);
    return 0;
}
