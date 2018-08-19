#include <cstdio>
using namespace std;
FILE *f=fopen("inversmodular.in","r");
FILE *g=fopen("inversmodular.out","w");
int inv,tmp,N,A;
int gcd(int a,int b,int &x,int &y)
{
    if(b==0)
    {
        x=1;
        y=0;
    }
    else
    {
        int x0,y0;
        gcd(b,a%b,x,y);
        x0=y;
        y0=x-y*(a/b);
        x=x0;
        y=y0;
    }
}
int main()
{
    scanf("%d %d",&A,&N);
    gcd(A,N,inv,tmp);
    if(inv<0) inv=N+(inv%N);
    printf("%d",inv);
    fclose(f);
    fclose(g);
    return 0;
}
