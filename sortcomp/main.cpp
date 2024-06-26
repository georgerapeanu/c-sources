#include <cstdio>
using namespace std;
FILE *f,*g;
long long n,i,v[500001];
void swap(long long &elem1,long long &elem2)
{
    long long temp;
    temp=elem1;
    elem1=elem2;
    elem2=temp;
}
void qsort(long long st, long long dr)
{
    long long i=st,j=dr,pivot=v[(st+dr)/2];
    while(i<=j)
    {
        while(v[i]<pivot) i++;
        while(v[j]>pivot) j--;
        if(i<=j)
        {
            swap(v[i],v[j]);
            i++;
            j--;
        }
    }
    if(i<dr)
    qsort(i,dr);
    if(j>st)
    qsort(st,j);
}
int main()
{
    f=fopen("algsort.in","r");
    fscanf(f,"%lld",&n);
    for(i=1;i<=n;i++)
    fscanf(f,"%lld",&v[i]);
    fclose(f);
    qsort(1,n);
    g=fopen("algsort.out","w");
    for(i=1;i<=n;i++)
    fprintf(g,"%lld ",v[i]);
    return 0;
}
