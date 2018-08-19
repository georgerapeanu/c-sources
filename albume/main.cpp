#include <cstdio>
using namespace std;
FILE *f=fopen("albume.in","r");
FILE *g=fopen("albume.out","w");
double rez,a,b;
long long C,K,Q;
int main()
{
    fscanf(f,"%lld %lld %lld",&C,&K,&Q);
    a=K*C-K+1;
    b=K*C-Q-K+1;
    rez=1;
    while(a<=K*C)
    {
        rez*=(b/a);
        a++;
        b++;
    }
    rez=1-rez;
    rez*=C;
    fprintf(g,"%.7f",rez);
    fclose(f);
    fclose(g);
    return 0;
}
