#include <cstdio>
#include <cstring>
#define MOD 100003
using namespace std;
FILE *f=fopen("spion.in","r");
FILE *g=fopen("spion.out","w");
long long i,x,y,N,K,poz=1,a,b,c;
char C[100005];
void gcd(long long a,long long b)
{
    if(b==0)
    {
        x=1;
        y=0;
    }
    else
    {
        gcd(b,a%b);
        long long xn,yn;
        xn=y;
        yn=x-y*(a/b);
        x=xn;
        y=yn;
    }
}
int main()
{
    fscanf(f,"%lld\n",&c);
    fgets(C,100005,f);
    N=strlen(C);
    if(C[N-1]=='\n')
        N--;
    for(i=0;i<N;i++)
    {
        if(C[i]=='E')
            poz++;
    }
    if(c==1)
    {fprintf(g,"%lld",poz);return 0;}
    poz--;
    a=b=c=1;
    for(i=2;i<=N;i++){
        if(i<=poz)
            a=(a*i)%MOD;
        if(i<=N-poz)
            b=(b*i)%MOD;
        c=(c*i)%MOD;
    }
    gcd(a,MOD);a=x;if(a<0)a=(a%MOD)+MOD;
    gcd(b,MOD);b=x;if(b<0)b=(b%MOD)+MOD;
    c=(((c*a)%MOD)*b)%MOD;
    fprintf(g,"%lld",c);
    fclose(f);
    fclose(g);
    return 0;
}
