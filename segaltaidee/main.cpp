#include <cstdio>
#include <cmath>
using namespace std;
FILE *f=fopen("seg.in","r");
FILE *g=fopen("seg.out","w");
double D[2][2][17][17];
int nxt[20];
int i;
int T,N;
double eval(int config)
{
    int nod=0,urm=nxt[0];
    double rez=0;
    for(int j=0;j<=i;j++,nod=urm,urm=nxt[urm])
    {
        int c1,c2;
        c1=(((1<<j)&config)==0);
        c2=(((1<<((j+1)%(i+1)))&config)!=0);
        rez+=D[c1][c2][nod][urm];
    }
    return rez;
}
double dist(double xa,double ya,double xb,double yb)
{
    return sqrt(pow(xa-xb,2)+pow(ya-yb,2));
}
int main()
{
    fscanf(f,"%d",&T);
    while(T)
    {
        fscanf(f,"%d",&N);
        for(int i=0;i<N;i++) fscanf(f,"%lf%lf%lf%lf",&D[0][0][i][i],&D[0][1][i][i],&D[1][0][i][i],&D[1][1][i][i]);
        for(int i=0;i<N;i++)
        {
            nxt[i]=0;
            for(int j=0;j<N;j++)
            {
                if(i!=j)
                {
                    D[0][0][i][j]=dist(D[0][0][i][i],D[0][1][i][i],D[0][0][j][j],D[0][1][j][j]);
                    D[0][1][i][j]=dist(D[0][0][i][i],D[0][1][i][i],D[1][0][j][j],D[1][1][j][j]);
                    D[1][0][i][j]=dist(D[1][0][i][i],D[1][1][i][i],D[0][0][j][j],D[0][1][j][j]);
                    D[1][1][i][j]=dist(D[1][0][i][i],D[1][1][i][i],D[1][0][j][j],D[1][1][j][j]);
                }
            }
        }
        for(i=1;i<N-1;i++)
        {
            double mini=(1<<16);
            int poz=0;
            for(int j=0;j<i;j++)
            {
                ///punere in lista
                nxt[i]=nxt[j];
                nxt[j]=i;
                ///evaluare pe configuratii
                for(int conf=0;conf<(1<<(i+1));conf++)
                {
                    double tmp=eval(conf);
                    if(tmp<mini)
                    {
                        mini=tmp;
                        poz=j;
                    }
                }
                ///scoatere din lista
                nxt[j]=nxt[i];
            }
            nxt[i]=nxt[poz];
            nxt[poz]=i;
        }
        i=N-1;
        double rez=(1<<16);
        for(int j=0;j<i;j++)
        {
            ///punere in lista
                nxt[i]=nxt[j];
                nxt[j]=i;
                ///evaluare pe configuratii
                for(int conf=0;conf<(1<<(i+1));conf++)
                {
                    double tmp=eval(conf);
                    if(tmp<rez)
                    {
                        rez=tmp;
                    }
                }
                ///scoatere din lista
                nxt[j]=nxt[i];
        }
        fprintf(g,"%.10f\n",rez);
        T--;
    }
    fclose(f);
    fclose(g);
    return 0;
}
