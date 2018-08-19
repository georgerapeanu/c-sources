#include <cstdio>
using namespace std;
FILE *f=fopen("compact2.in","r");
FILE *g=fopen("compact2.out","w");
int i,j,V,N,ctr,best;
bool ok;
typedef struct{int x,y;} data;
data grupe[1000005];
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V);
        ok=0;
        for(j=1;j<=ctr;j++)
            if(grupe[j].x-1==V)
            {
                ok=1;
                grupe[j].x=V;
            }
            else if(grupe[j].y+1==V)
            {
                ok=1;
                grupe[j].y=V;
            }
        if(!ok)
        {
            ctr++;
            grupe[ctr].x=grupe[ctr].y=V;
        }
    }
    for(i=1;i<=N;i++)
        if(grupe[i].y-grupe[i].x+1>best)
        best=grupe[i].y-grupe[i].x+1;
    fprintf(g,"%d",best);
    return 0;
}
//x-minim
//y-maxim
