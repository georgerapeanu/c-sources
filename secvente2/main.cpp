#include <cstdio>
using namespace std;
FILE *f=fopen("secvente2.in","r");
FILE *g=fopen("secvente2.out","w");
int val[1000005],st,dr,a,i,N,maxim;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&a);
        st=dr=a;
        if(val[a-1])
            st=val[a-1];
        if(val[a+1])
            dr=val[a+1];
        maxim=maxim>dr-st+1 ? maxim:dr-st+1;
        val[st]=dr;
        val[dr]=st;
        fprintf(g,"%d\n",maxim);
    }
    return 0;
}
