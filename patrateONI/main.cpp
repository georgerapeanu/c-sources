#include <cstdio>
#include <cmath>
using namespace std;
FILE *f=fopen("patrate2.in","r");
FILE *g=fopen("patrate2.out","w");
int nr,N,M,i,nrmat,a,total,prod,poz,j,rand,coloana;
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%d",&a);
        nr=nr+(1<<(a-1));
        if(!nrmat)
            nrmat=a;
    }
    fprintf(g,"%d\n",nr);
    total=1<<(N-1);

    total=ceil(sqrt(total));
    poz=((nr>>(nrmat))<<(nrmat-1))+(nr-((nr>>(nrmat-1))<<(nrmat-1)));
    rand=poz%total+1;
    coloana=poz/total+1;
    fprintf(g,"%d %d",rand,coloana);
    fclose(f);
    fclose(g);
    return 0;
}
