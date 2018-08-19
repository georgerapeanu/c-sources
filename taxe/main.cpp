#include <cstdio>
using namespace std;
FILE *f=fopen("taxe.in","r");
FILE *g=fopen("taxe.out","w");
long long S,i,st=1,dr,mid,last;
long long ok(long long nr)
{
    long long s=0;
    while(nr)
    {
        s+=nr;
        nr/=4;
    }
    return s;
}
int main()
{
    fscanf(f,"%lld",&S);
    dr=S/4;
    S/=4;
    last=-1;
    while(st<=dr)
    {
        mid=(st+dr)/2;
        if(ok(mid)<=S)
        {
            last=mid;
            st=last+1;
        }
        else
            dr=mid-1;
    }
    fprintf(g,"%lld",last);
    fclose(f);
    fclose(g);
    return 0;
}
