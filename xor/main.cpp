#include <cstdio>
using namespace std;
FILE *f,*g;
int n,i;
long long a[2001],p,k,maxim,x1,x2,x3;
int main()
{
    f=fopen("xor1.in","r");
    g=fopen("xor1.out","w");
    fscanf(f,"%d",&n);
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%lld",&a[i]);
        x3=x3^a[i];
    }
    fclose(f);
    x3=(x3|a[1])^(x3&a[1]);
    for(p=1;p<=n-2;p++)
    {
        x1=x1^a[p];
        for(k=p+1;k<=n-1;k++)
        {
            x2=x2^a[k];
            x3=(x3|a[k])^(x3&a[k]);
            if(x1+x2+x3>maxim)
            maxim=x1+x2+x3;
        }
        x3=x3^x2;
        x3=(x3|a[p+1])^(x3&a[p+1]);
        x2=0;
    }
    fprintf(g,"%lld",maxim);
    fclose(g);
    return 0;
}
