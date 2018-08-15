#include <cstdio>
#include <queue>
using namespace std;
FILE *f=fopen("tarabe.in","r");
FILE *g=fopen("tarabe.out","w");
long long N,K,rez;
long long A[200005];
long long B[200005],S,nr;
long long check(long long p)
{
    nr=0;S=0;
    for(int i=1;i<=N;i++)
    {
        if(A[i]>p)continue;
        long long x=(p-A[i])/B[i]+1;
        nr+=x;
        S+=x*A[i]+B[i]*(x-1)*x/2;
    }
    return nr;
}
int main()
{
    fscanf(f,"%lld %lld",&N,&K);
    for(int i=1;i<=N;i++)
        fscanf(f,"%lld %lld",&B[i],&A[i]);
    long long st=1;
    long long dr=1;
    while(check(dr)<K)dr<<=1;
    while(dr-st>1)
    {
        long long mid=(st+dr)/2;
        if(check(mid)<K)
            st=mid;
        else
            dr=mid;
    }
    check(dr);
    rez=S-(nr-K)*dr;
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
