#include <cstdio>
using namespace std;
FILE *f=fopen("cover1.in","r");
FILE *g=fopen("cover1.out","w");
int a,L;
long long power(long b,long n)
{
    long p=1;
    while(n)
    {
        if(n%2) p=(p*b)%10003;
        b=(b*b)%10003;
        n/=2;
    }
    return p;
}
int main()
{
    fscanf(f,"%d",&L);
    a=power(3,L-1);
    a*=2;
    a%=10003;
    fprintf(g,"%d",a);
    fclose(f);
    fclose(g);
    return 0;
}