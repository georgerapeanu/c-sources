#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("donald.in","r");
FILE *g=fopen("donald.out","w");
typedef struct {double x,y;} punct;
punct V[305];
int i,N,j,nr,mnr,k;
double a,b;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%lf %lf",&V[i].x,&V[i].y);
    }
    for(i=1;i<=N;i++)
    {
        for(j=i+1;j<=N;j++)
        {
            if(i!=j)
            {
                a=V[i].x-V[j].x;
                b=V[i].y-V[j].y;
                nr=2;
                for(k=1;k<=N;k++)
                {
                    if(i!=k&&j!=k)
                    {
                        if(a==0)
                        {
                            if(V[k].x==V[i].x)
                                nr++;
                        }
                        else if(b==0)
                        {
                            if(V[k].y==V[i].y)
                                nr++;
                        }
                        else
                        {
                            if((V[k].x-V[j].x)/a==(V[k].y-V[j].y)/b)
                                nr++;
                        }
                    }
                }
                mnr=max(mnr,nr);
            }
        }
    }
    fprintf(g,"%d",mnr);
    return 0;
}
