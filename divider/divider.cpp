#include <cstdio>
#include <set>
using namespace std;
long long i,j,n,a,b,powa,powb;
set <long long> V;
set <long long> :: iterator it;
FILE *f=fopen("divider.in","r"),*g=fopen("divider.out","w");
long long power(long long a,long long n)
{
    long long rez=1;
    while(n)
    {
        if(n%2==1)
        {
            rez*=a;
        }
        a=a*a;
        n/=2;
    }
    return rez;
}
int main()
{
    fscanf(f,"%lld%lld%lld",&a,&b,&n);
    powa=power(a,n);
    powb=power(b,n);
    for(i=1;i<=powa;i*=a)
    {
        for(j=1;j<=powb;j*=b)
        {
            V.insert(i*j);
        }
    }
    for(it=V.begin();it!=V.end();it++)
    {
            fprintf(g,"%lld ",*it);
    }
    fclose(f);
    fclose(g);
    return 0;
}
