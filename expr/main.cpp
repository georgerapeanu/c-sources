#include <cstdio>
#include <cstdlib>
using namespace std;
FILE *f,*g;
int n,m,a[100],b[100],i,k,p,q;
long long rez;
int compare(const void * a, const void * b)
{
    return *(int*)a-*(int*)b;
}
int main()
{
    f=fopen("expresie.in","r");
    fscanf(f,"%d %d",&n,&m);
    for(i=1;i<=n;i++)
    fscanf(f,"%d",&a[i]);
    for(i=1;i<=m;i++)
    fscanf(f,"%d",&b[i]);
    fclose(f);
    qsort(a,n,sizeof(int),compare);
    qsort(b,m,sizeof(int),compare);
    i=n;j=m;
    while(a[i]>0&&b[j]>0&&k!=n)
    {
        rez+=a[i--]*b[j--];
        k++;
    }
    p=i;q=j;
    i=j=0;
    while(a[i++]<0&&b[j++]<0&&k!=n)
    {
        k++;
        rez+=a[i]*b[j];
    }
    return 0;
}
