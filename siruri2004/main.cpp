#include <cstdio>
using namespace std;
FILE *f,*g;
int n,x[200],y[200]={1},i,j;
int main()
{
    f=fopen("siruri.in","r");
    fscanf(f,"%d",&n);
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%d",&x[i]);
    }
    fclose(f);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(i!=j)
            {
                if(x[i]>x[j])
                {
                    y[i]++;
                }
            }
        }
    }
    g=fopen("siruri.out","w");
    for(i=1;i<=n;i++)
    fprintf(g,"%d ",y[i]+1);
    fclose(g);
    return 0;
}
