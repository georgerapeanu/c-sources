#include <cstdio>
using namespace std;
FILE *f,*g;
int i,n;
long long rez=1,nr;
int main()
{
    f=fopen("reducere.in","r");
    fscanf(f,"%d",&n);
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%lld",&nr);
        rez=(rez*(nr+1))%666013;
    }
    fclose(f);
    g=fopen("reducere.out","w");
    if(!rez)
        rez=666013;
    fprintf(g,"%lld",rez-1);
    fclose(g);
    return 0;
}
