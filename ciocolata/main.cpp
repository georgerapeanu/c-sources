#include <cstdio>
using namespace std;
FILE *f=fopen("ciocolata.in","r");
FILE *g=fopen("ciocolata.out","w");
int N,M,m[505][505],i,j,v[505],suma,maximsuma,maxs,k;
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            fscanf(f,"%d",&m[i][j]);
        }
    }
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=N;j++)
            v[j]=0;
        for(j=i;j<=N;j++)
        {
            for(k=1;k<=M;k++)
            v[k]+=m[j][k];
            maxs=-1;
            suma=0;
            for(k=1;k<=M;k++)
            {
                suma+=v[k];
                if(suma>maxs)
                maxs=suma;
                if(suma<0)
                    suma=0;
            }
            if(maximsuma<maxs)
                maximsuma=maxs;
        }
    }
    fprintf(g,"%d",maximsuma);
    return 0;
}
