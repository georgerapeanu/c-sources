#include <cstdio>
#include <cassert>
using namespace std;
int V[64000],i,N,M[105][105][105],nivel,nr,j,n2,minim,ppoz,dirx,diry;
FILE *f=fopen("suma4.in","r");
FILE *g=fopen("suma4.out","w");
int main()
{
    fscanf(f,"%d",&N);
    assert(1<=N&&N<=63365);
    for(i=1;i<=N;i++)
    {
        nr++;
        if(nr>nivel*nivel)
        {
                nr=1;
            nivel++;
        }
        fscanf(f,"%d",&V[i]);
    }
    n2=nivel;
    nr=N;
    while(nivel)
    {
        ppoz=nr-nivel*nivel+1;
        for(i=1;i<=nivel;i++)
        {
            for(j=1;j<=nivel;j++)
            {
                minim=M[nivel+1][i][j];
                if(M[nivel+1][i][j+1]<minim)
                {
                    minim=M[nivel+1][i][j+1];
                }
                if(M[nivel+1][i+1][j]<minim)
                {
                    minim=M[nivel+1][i+1][j];
                }
                if(M[nivel+1][i+1][j+1]<minim)
                {
                    minim=M[nivel+1][i+1][j+1];
                }
                M[nivel][i][j]=minim+V[ppoz+N-nr];
                nr--;
            }
        }
                N-=nivel*nivel;
        nivel--;
    }
    fprintf(g,"%d %d\n",n2,M[1][1][1]);
    i=j=1;nr=0;
    for(nivel=1;nivel<=n2;nivel++)
    {
         minim=M[nivel+1][i][j];dirx=diry=0;
                if(M[nivel+1][i][j+1]<minim)
                {
                    minim=M[nivel+1][i][j+1];
                    diry=1;
                    dirx=0;
                }
                if(M[nivel+1][i+1][j]<minim)
                {
                    minim=M[nivel+1][i+1][j];
                    dirx=1;
                    diry=0;
                }
                if(M[nivel+1][i+1][j+1]<minim)
                {
                    minim=M[nivel+1][i+1][j+1];
                    dirx=diry=1;
                }
            fprintf(g,"%d ",nr+(i-1)*nivel+j);
            i+=dirx;
            j+=diry;
        nr+=nivel*nivel;
    }
    fclose(f);
    fclose(g);
    return 0;
}
