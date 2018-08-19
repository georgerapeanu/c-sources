#include <cstdio>
using namespace std;
short n,i;
unsigned long long fact=1;
bool used[21],a;
int main()
{
    FILE *g,*f;
    f=fopen("npermunic.in","r");
    g=fopen("npermunic.out","w");
    fscanf(f,"%hd",&n);
    if(n%2==0)
    {
        for(i=1;i<=n/2;i++)
        fact=fact*i*(n-i+1);
    }
    else
    {
        for(i=1;i<=n/2;i++)
        fact=fact*i*(n-i+1);
        fact*=(n/2+1);
    }
    for(i=1;i<=n;i++)
    {
        fprintf(f,"%hd",&a);
        if(used[a]==0)
        used[a]=1;
        else
        fact-=n;
    }
    if(fact==0)
    fact=1;
    fprintf(g,"%llu",fact);
    fclose(f);
    fclose(g);
    return 0;
}
