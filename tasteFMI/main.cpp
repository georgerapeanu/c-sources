#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("taste.in","r");
FILE *g=fopen("taste.out","w");
long long b,a;
long long reza,rezb=(1LL<<62);
long long X,Y;
int main()
{
    fscanf(f,"%lld%lld",&X,&Y);
    b=0;
    while(Y>>b)
    {
        if(((X>>b)<<b)==X) a=(X>>b);
        else
        {
            a=(X>>b)+1;
            if((X>>b)+1>(Y>>b)) break;
        }
        a=max(a,1LL);
        if(a+b<reza+rezb){reza=a;rezb=b;}
        b++;
    }
    fprintf(g,"%lld %lld",reza,rezb);
    return 0;
}
