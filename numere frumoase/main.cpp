#include <cstdio>
using namespace std;
FILE *f, *g;
int main()
{
    unsigned long long n2=2,n3=3,n5=5,i=1,j=1,k=1,l,a[1000],t,n;
    for(int i=0;i<1000;i++)
    a[i]=0;
    a[1]=1;l=1;
    f=fopen("numere.in","r");
    fscanf(f,"%llu",&n);
    fclose(f);
    g=fopen("numere.out","w");
    while(l!=n)
    {
        t=n2;
        if(n3<t)
        t=n3;
        if(n5<t)
        t=n5;
        if(t!=a[l])
        a[++l]=t;
        if(t==n2)
        {
            i++;
            n2=2*a[i];
        }
        else if(t==n3)
        {
            j++;
            n3=3*a[j];
        }
        else
        {
            k++;
            n5=5*a[k];
        }
    }
    for(int i=1;i<=l;i++)
    fprintf(g,"%llu ",a[i]);
    fclose(g);
    return 0;
}
