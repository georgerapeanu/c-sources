#include <cstdio>
using namespace std;
FILE *f=fopen("bursa.in","r");
FILE *g=fopen("bursa.out","w");
int N,S,c[600],v[600],i,j,actiuni,r,suma,x,y,maxim;
int main()
{
    fscanf(f,"%d %d",&N,&S);
    maxim=S;
    for(i=1;i<=N;i++)
        fscanf(f,"%d",&c[i]);
    for(i=1;i<=N;i++)
        fscanf(f,"%d",&v[i]);
    for(i=1;i<=N;i++)
    {
        actiuni=S/c[i];
        r=S%c[i];
        for(j=i+1;j<=N;j++)
        {
            suma=r+v[j]*actiuni;
            if(suma>maxim)
            {maxim=suma;x=i;y=j;}
        }
    }
    if(maxim!=S)
        fprintf(g,"%d\n%d %d",maxim,x,y);
    else
        fprintf(g,"%d\n-1 -1",S);
    fclose(f);
    fclose(g);
    return 0;
}
