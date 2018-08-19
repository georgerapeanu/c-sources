#include <cstdio>
using namespace std;
FILE *f=fopen("meteo1.in","r");
FILE *g=fopen("meteo1.out","w");
int n,i,V[1010],maxim,lg,x,bestx;
int main()
{
    lg=1;
    maxim=1;
    x=1;
    fscanf(f,"%d",&n);
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%d",&V[i]);
    }
    for(i=2;i<=n;i++)
    {
        if((V[i-1]<0&&V[i]>=0)||(V[i-1]>=0&&V[i]<0))
        {
            lg++;
        }
        else
        {
            if(lg>=maxim)
            {
                maxim=lg;
                bestx=x;
            }
            x=i;
            lg=1;
        }
    }
     if(lg>=maxim)
            {
                maxim=lg;
                bestx=x;
            }
    if(maxim!=1)
    {
    fprintf(g,"%d\n",maxim);
    for(i=bestx;i<=bestx+maxim-1;i++)
    {
        fprintf(g,"%d ",V[i]);
    }
    }
    else
    fprintf(g,"0");
    fclose(f);
    fclose(g);
    return 0;
}
