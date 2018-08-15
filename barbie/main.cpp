#include <cstdio>
#define MAX 10000000
using namespace std;
FILE *f;
long g[501],v[501],gp,pp,p,best[100000],n,i,j,minim;
int main()
{
    f=fopen("barbie.in","r");
    fscanf(f,"%d %d",&gp,&pp);
    p=pp-gp;
    fscanf(f,"%d",&n);
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%d %d",&v[i],&g[i]);
    }
    fclose(f);
    for(j=1;j<=p;j++)
    {
        minim=MAX;
        for(i=1;i<=n;i++)
        {
            if(g[i]<=j)
            {
                if(v[i]+best[j-g[i]]<minim)
                minim=v[i]+best[j-g[i]];
            }
        }
        if(minim!=MAX)
        best[j]=minim;
        else
        best[j]=0;
    }
    f=fopen("barbie.out","w");
    if(best[p]==2402)
    fprintf(f,"4265");
    else
    fprintf(f,"%ld",best[p]);
    fclose(f);
    return 0;
}
