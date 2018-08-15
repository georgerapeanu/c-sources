#include <cstdio>
using namespace std;
FILE *f=fopen("mafia.in","r");
FILE *g=fopen("mafia.out","w");
int N,a,i;
long long rez,maxim;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&a);
        rez+=a;
        if(a>maxim)
            maxim=a;
    }
    if(rez%(N-1)!=0)
        rez=rez/(N-1)+1;
    else
        rez=rez/(N-1);
    if(rez>maxim)
        fprintf(g,"%lld",rez);
    else
        fprintf(g,"%lld",maxim);
    return 0;
}
