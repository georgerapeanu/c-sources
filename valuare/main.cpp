#include <cstdio>
using namespace std;
long long b,p,a,i,rez;
int main()
{
    FILE *f;
    f=fopen("valuare.in","r");
    fscanf(f,"%lld %lld",&b,&p);
    fclose(f);
    b=b%p;
    a=1;
    for(i=b-1;i>0;i--)
    {
        rez=(rez+(i*a)%p)%p;
        a=(a*b)%p;
    }
    f=fopen("valuare.out","w");
    fprintf(f,"%lld",rez);
    fclose(f);
    return 0;
}
