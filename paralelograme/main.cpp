#include <cstdio>
using namespace std;
FILE *f=fopen("paralelograme.in","r");
FILE *g=fopen("paralelograme.out","w");
long long N,M,h,w,GCD[2005][2005],i,j,rez,aux;
int main()
{
    fscanf(f,"%lld %lld",&N,&M);
    for(i=1;i<=N;i++)
        GCD[i][0]=i;
    for(i=1;i<=N;i++)
        for(j=1;j<=M;j++)
            if(j>i)
                GCD[i][j]=GCD[i][j%i];
            else
                GCD[i][j]=GCD[j][i%j];
    for(h=2;h<=N+1;h++)
        for(w=2;w<=M+1;w++)
        {
            aux=(h-2)*(w-2)+h*w-GCD[h-1][w-1]-2;///cazul 1 e clar.cazul 2 este 2(diagonala cealalta)*(jumate din patrat -jumate din CGD(degenerate)-1(vf));
            rez+=aux*(N-h+2)*(M-w+2);
        }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
