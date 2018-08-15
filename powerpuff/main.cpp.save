#include <cstdio>
using namespace std;
FILE *f=fopen("powerpuff.in","r");
FILE *g=fopen("powerpuff.out","w");
int N;
long long x1,x2,x3,a,i;
int adaugare(long long a,long long b)
{
    int suma=0;
    int A[]={0,0,0,0,0,0,0,0,0,0};
    int B[]={0,0,0,0,0,0,0,0,0,0};
    while(a!=0)
    {
        A[a%10]++;
        a/=10;
    }
     while(b!=0)
    {
        B[b%10]++;
        b/=10;
    }
    for(int i=0;i<10;i++)
    {
        if(A[i]&&!B[i])
            suma+=A[i]*i;
        else if(!A[i]&&B[i])
            suma-=B[i]*i;
    }
    return suma;
}
int main()
{
    fscanf(f,"%lld %lld %lld %lld",&x1,&x2,&x3,&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%lld",&a);
        x1=x1+adaugare(x1,a);
        x2=x2+adaugare(x2,a);
        x3=x3+adaugare(x3,a);
    }
    fprintf(g,"%lld\n%lld\n%lld",x1,x2,x3);
    return 0;
}
