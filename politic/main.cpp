#include <cstdio>
using namespace std;
FILE *f=fopen("politic.in","r");
FILE *g=fopen("politic.out","w");
int nrelem[20005],M;
int felem,elem;
long long nr;
int N,i,j;
int main()
{
    fscanf(f,"%d%d",&N,&felem);
    nrelem[1]=1;
    nrelem[0]=1;
    for(i=2;i<=N;i++)
    {
        fscanf(f,"%d",&elem);
        if(felem==elem-1)
        {
            nrelem[nrelem[0]]++;
        }
        else
        {
            nrelem[++nrelem[0]]++;
        }
        felem=elem;
    }
    fprintf(g,"%d\n",nrelem[0]);
    N=N/2+1;
    j=1;
    for(i=2;i<=nrelem[0];i++)
        nrelem[i]+=nrelem[i-1];
    M=nrelem[0];
    nrelem[0]=0;
    for(i=1;i<=M;i++)
    {
        while(nrelem[j]-nrelem[i-1]<N&&j<=M)
            j++;
        nr+=M-j+1;
    }
    fprintf(g,"%lld",nr);
    fclose(f);
    fclose(g);
    return 0;
}
