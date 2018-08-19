#include <cstdio>
using namespace std;
FILE *f=fopen("magic7.in","r");
FILE *g=fopen("magic7.out","w");
int N,P;
long long C,nr=1;
int main()
{
    fscanf(f,"%lld %d %d",&C,&N,&P);
    N--;
    while(N)
    {
        if(N%2==1)
        {nr*=C;nr%=P;}
        C=C*C;
        C%=P;
        N/=2;
    }
    if(nr==0)
        nr=P;
    fprintf(g,"%lld",nr);
    return 0;
}
