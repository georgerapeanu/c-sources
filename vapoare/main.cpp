#include <cstdio>
using namespace std;
unsigned long long z1,z2,x,y;
unsigned long long gcd(unsigned long long a,unsigned long long b)
{
    if(b==0)
    return a;
    return gcd(b,a%b);
}
int main()
{
    FILE *f;
    f=fopen("vapoare.in","r");
    fscanf(f,"%llu %llu %llu %llu",&x,&y,&z1,&z2);
    fclose(f);
    x=(x<<1)*7+z1;
    y=(y<<1)*7+z2;
    f=fopen("vapoare.out","w");
    fprintf(f,"%llu",(x*y/gcd(x,y)));
    fclose(f);
    return 0;
}
