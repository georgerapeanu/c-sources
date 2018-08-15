#include <cstdio>
using namespace std;
FILE *f,*g;
int l[200],poz[200],v[200],i,j,n,prim;
int main()
{
    f=fopen("input.in","r");
    fscanf(f,"%d",&n);
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%d",&v[i]);
    }
    fclose(f);
    l[n]=1;poz[n]=-1;
    for(i=n-1;i>0;i--)
    {
        l[i]=1;poz[i]=-1;
        for(j=i+1;j<=n;j++)
        {
            if(v[i]<v[j]&&l[i]<l[j]+1)
            {
                l[i]=1+l[j];
                poz[i]=j;
            }
        }
    }
    g=fopen("input.out","w");
    for(i=1;i<=n;i++)
    {
        prim=l[prim]>l[i] ? prim:i;
    }
    fprintf(g,"%d\n",prim);
    i=prim;
    while(i!=-1)
    {
        fprintf(g,"%d ",v[i]);
        i=poz[i];
    }
    fclose(g);
    return 0;
}
