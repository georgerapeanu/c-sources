#include <cstdio>
#include <cmath>
#include <algorithm>
#define x first
#define y second
using namespace std;
FILE *f=fopen("seg.in","r");
FILE *g=fopen("seg.out","w");
typedef pair<double,double> point;
int N;
int T;
double D[1<<17][2][17],d[2][2][17][17];
double dist(double xa,double ya,double xb,double yb)
{
    return sqrt(pow(xb-xa,2)+pow(yb-ya,2));
}
int main()
{
    fscanf(f,"%d",&T);
    while(T)
    {
        fscanf(f,"%d",&N);
        for(int i=0;i<N;i++)
        {
            fscanf(f,"%lf%lf%lf%lf",&d[0][0][i][i],&d[0][1][i][i],&d[1][0][i][i],&d[1][1][i][i]);
        }
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                if(i==j) continue;
                d[0][0][i][j]=dist(d[0][0][i][i],d[0][1][i][i],d[0][0][j][j],d[0][1][j][j]);
                d[0][1][i][j]=dist(d[0][0][i][i],d[0][1][i][i],d[1][0][j][j],d[1][1][j][j]);
                d[1][0][i][j]=dist(d[1][0][i][i],d[1][1][i][i],d[0][0][j][j],d[0][1][j][j]);
                d[1][1][i][j]=dist(d[1][0][i][i],d[1][1][i][i],d[1][0][j][j],d[1][1][j][j]);
            }
        }
        for(int i=0;i<2;i++) for(int j=0;j<N;j++) D[1][i][j]=(1<<14);
        D[1][0][0]=0;
        for(int conf=3;conf<(1<<N);conf+=2)
        {
            for(int cap=0;cap<2;cap++)
            {
                for(int segm=0;segm<N;segm++)
                {
                    D[conf][cap][segm]=(1<<14);
                    if(!segm) continue;
                    if((1<<segm)&conf)
                    {
                        for(int ncap=0;ncap<2;ncap++)
                        {
                            for(int nsegm=0;nsegm<N;nsegm++)
                            {
                                if(nsegm!=segm&&((1<<nsegm)&conf))
                                {
                                    D[conf][cap][segm]=min(D[conf][cap][segm],D[conf-(1<<segm)][ncap][nsegm]+d[1-ncap][cap][nsegm][segm]);
                                }
                            }
                        }
                    }
                }
            }
        }
        int conf=(1<<N)-1;
        double rez=(1<<14);
        for(int cap=0;cap<2;cap++)
        {
            for(int segm=1;segm<N;segm++)
            {
                rez=min(rez,D[conf][cap][segm]+d[1-cap][0][segm][0]);
            }
        }
        fprintf(g,"%.10f\n",rez);
        T--;
    }
    return 0;
}
