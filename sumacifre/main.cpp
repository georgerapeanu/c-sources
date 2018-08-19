#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("sumacifre.in","r");
FILE *g=fopen("sumacifre.out","w");
long long p10=1,N,K,nr,suma,i,a,uc;
int main()
{
    fscanf(f,"%lld %lld",&N,&K);
    fclose(f);
    for(i=1;i<=K;i++)
    {
        nr=0;
        p10=1;
        a=N;
        uc=a%10;
        a=a/10;
        while(a)
        {
            nr=nr+abs(uc-a%10)*p10;
            p10*=10;
            uc=a%10;
            a/=10;
        }
        if(nr)
        N=nr;
        suma+=N;
    }
    fprintf(g,"%lld ",suma);
    fclose(f);
    fclose(g);
    return 0;
}
