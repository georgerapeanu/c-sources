#include <cstdio>
using namespace std;
FILE *f,*g;
unsigned long long n1,k,n2,v[200000],i,temp;
int main()
{
    f=fopen("rotk.in","r");
    g=fopen("rotk.out","w");
    fscanf(f,"%llu",&n1);
    for(i=0;i<n1;i++)
    fscanf(f,"%llu",&v[i]);
    fscanf(f,"%llu",&k);
    for(i=0;i<k/2;i++)
    {
        temp=v[i];
        v[i]=v[k-i-1];
        v[k-i-1]=temp;
    }
    for(i=k;i<(n1+k)/2;i++)
    {
        temp=v[i];
        v[i]=v[n1+k-1-i];
        v[n1+k-1-i]=temp;
    }
    for(i=0;i<n1/2;i++)
    {
        temp=v[i];
        v[i]=v[n1-i-1];
        v[n1-i-1]=temp;
    }
     fscanf(f,"%llu",&n2);
    for(i=n1;i<n1+n2;i++)
    fscanf(f,"%llu",&v[i]);
    fscanf(f,"%llu",&k);
    for(i=n1;i<n1+k/2;i++)
    {
        temp=v[i];
        v[i]=v[n1+k-1-(i-n1)];
        v[n1+k-1-(i-n1)]=temp;
    }
    for(i=n1+k;i<(n1+k+n1+n2)/2;i++)
    {
        temp=v[i];
        v[i]=v[n1+n2-(i-n1-k)-1];
        v[n1+n2-(i-n1-k)-1]=temp;
    }
    for(i=n1;i<(n1+n2+n1)/2;i++)
    {
        temp=v[i];
        v[i]=v[n1+n2-(i-n1)-1];
        v[n1+n2-(i-n1)-1]=temp;
    }
    fscanf(f,"%llu",&k);
    for(i=0;i<k/2;i++)
    {
        temp=v[i];
        v[i]=v[k-i-1];
        v[k-i-1]=temp;
    }
    for(i=k;i<(n1+n2+k)/2;i++)
    {
        temp=v[i];
        v[i]=v[n1+n2-(i-k)-1];
        v[n1+n2-(i-k)-1]=temp;
    }
   for(i=0;i<(n1+n2)/2;i++)
    {
        temp=v[i];
        v[i]=v[n1+n2-i-1];
        v[n1+n2-i-1]=temp;
    }
    for(i=0;i<n1+n2;i++)
    fprintf(g,"%llu ",v[i]);
    fclose(f);
    fclose(g);
    return 0;
}
