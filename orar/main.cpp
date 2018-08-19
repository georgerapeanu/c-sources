#include <cstdio>
#include <cstdlib>
using namespace std;
FILE *f,*g;
int n,q,a[200001],x,y,i,j;
int folos[200001];
long long suma;
long temp;
int comp(const void *a,const void *b)
{
    return (*(int*)a-*(int*)b);
}
int main()
{
    f=fopen("orar.in","r");
    fscanf(f,"%d",&n);
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%d",&a[i]);
        temp+=a[i];
    }
    qsort(a,n+1,sizeof(int),comp);
    fscanf(f,"%d",&q);
    for(i=1;i<=q;i++)
    {
        fscanf(f,"%d %d",&x,&y);
        if(x!=1&&y!=n)
        for(j=x;j<=y;j++)
        {
            folos[j]++;
        }
        else
        suma+=temp;
    }
    fclose(f);
    qsort(folos,n+1,sizeof(int),comp);
    for(i=n;i>=1;i--)
    {
        suma+=folos[i]*a[i];
    }
    g=fopen("orar.out","w");
    fprintf(f,"%lld",suma);
    fclose(g);
    return 0;
}
