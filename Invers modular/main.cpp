#include <cstdio>
#define ll long long
using namespace std;
FILE *f=fopen("inversmodular.in","r");
FILE *g=fopen("inversmodular.out","w");
void gcd(ll a,ll b,ll &x,ll &y)
{
    if(!b)
    {
        x=1;
        y=0;
        return ;
    }
    ll x0,y0;
    gcd(b,a%b,x0,y0);
    x=y0;
    y=x0-(a/b)*y0;
}
///a*x+b*y=1
///b*x+(a-[a/b]*b)*y=1
///a*y+b(x-[a/b]*y)=1
ll X,N;
int main()
{
    fscanf(f,"%lld%lld",&X,&N);
    ll inv,tmp;
    gcd(X,N,inv,tmp);
    fprintf(g,"%lld",(inv%N+N)%N);
    fclose(f);
    fclose(g);
    return 0;
}
