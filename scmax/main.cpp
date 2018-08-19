#include <cstdio>
using namespace std;
FILE *f=fopen("scmax.in","r"),*g=fopen("scmax.out","w");
int best[100005],V[100005],i,n,j,maxim,F[100005],x,rez[100005];
int main()
{
    fscanf(f,"%d",&n);
    for(i=1;i<=n;i++)
    fscanf(f,"%d",&V[i]);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<i;j++)
        {
            if(V[j]<V[i])
            {
                if(best[j]+1>best[i])
                {
                    F[i]=j;
                    best[i]=best[j]+1;
                }
            }
        }
        if(maxim<best[i])
        {
            maxim=best[i];
            x=i;
        }
    }
    fprintf(g,"%d\n",maxim+1);
    while(x)
    {
        rez[++rez[0]]=V[x];
        x=F[x];
    }
    for(i=rez[0];i>0;i--)
    {
        fprintf(g,"%d ",rez[i]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
