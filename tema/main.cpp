#include <cstdio>
#define in "tema.in"
#define out "tema.out"
using namespace std;
FILE *f,*g;
int n,m,i,nr;
bool este[101];
int main()
{
    f=fopen(in,"r");
    g=fopen(out,"w");
    fscanf(f,"%d %d",&n,&m);
    for(i=1;i<=m;i++)
    {
        fscanf(f,"%d",&nr);
        este[nr]=1;
    }
    for(i=1;i<=n;i++)
    if(este[i]==0)
    fprintf(g,"%d ",i);
    fclose(f);
    fclose(g);
    return 0;
}
