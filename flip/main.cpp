#include <cstdio>
#include <bitset>
using namespace std;
FILE *f=fopen("flip.in","r");
FILE *g=fopen("flip.out","w");
int m[20][20],i,j,N,M,linie,suma,S,maxim;
bitset <20> rez;
void bl(int pas)
{
    if(pas==N+1)
    {
        S=0;
        for(j=1;j<=M;j++)
        {
            suma=0;
            for(i=1;i<=N;i++)
            {
                if(rez[i]==1)
                    suma+=m[i][j]*-1;
                else
                    suma+=m[i][j];
            }
            if(suma<0)
                suma*=-1;
            S+=suma;
        }
        if(maxim<S)
        maxim=S;
    }
    else
    {
        rez[pas]=0;
        bl(pas+1);
        rez[pas]=1;
        bl(pas+1);
    }
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
            fscanf(f,"%d",&m[i][j]);
    }
    bl(1);
    fprintf(g,"%d",maxim);
    fclose(f);
    fclose(g);
    return 0;
}