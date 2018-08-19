#include <cstdio>
using namespace std;
FILE *f,*g;
int a,v[101],v2[101],n,i,nr,ci,temp;
int main()
{
    f=fopen("cutii.in","r");
    g=fopen("cutii.out","w");
    fscanf(f,"%d",&n);
    for(i=1;i<=n+1;i++)
    fscanf(f,"%d",&v[i]);
    for(i=1;i<=n+1;i++)
    {
        fscanf(f,"%d",&a);
        v2[a]=i;
        if(a==0)
        v2[a]=0;
    }
    for(i=1;i<=n+1;i++)
    {
        ci=i;
        while(v2[v[ci]]!=0)
        {
            nr++;
            temp=ci;
            ci=v[v2[v[ci]]];
            v2[v[temp]]=0;
        }
    }
    fprintf(g,"%d",nr);
    fclose(f);
    fclose(g);
    return 0;
}
//0 3 5 1 2
