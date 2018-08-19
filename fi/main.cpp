#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("fi.in","r");
FILE *g=fopen("fi.out","w");
long long N,M,K,P,a,b;
long long st,dr,nr;
int main()
{
    fscanf(f,"%lld %lld\n%lld %lld\n%lld %lld",&N,&M,&K,&P,&a,&b);
    while(true)
    {
        st=min(K,b-1);
        dr=min(K,M-b);
        if(P>2*st+dr+1)
        {
            a++;
            b=b+dr;
            nr+=st+dr+1;
            P-=2*st+dr+1;
        }
        else
        {
            if(P<=st)
            {
                nr+=P;
                b-=(P-1);
                break;
            }
            else
            {
                b=b-st+P-st-1;
                nr+=st+max(0LL,P-2*st-1)+1;
                break;
            }
        }
    }
    fprintf(g,"%lld %lld\n%lld",a,b,nr);
    fclose(f);
    fclose(g);
    return 0;
}
