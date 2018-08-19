#include <cstdio>
#include <algorithm>
#define inf 40005
using namespace std;
FILE *f=fopen("soricel1.in","r");
FILE *g=fopen("soricel1.out","w");
int N,M,ad,i,j,minim=inf,dist,x,y;
typedef struct {int x,y;} POINT;
POINT A[505];
POINT D[505];
int main()
{
    fscanf(f,"%d %d",&N,&M);
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d %d",&A[i].x,&A[i].y);
    }
    fscanf(f,"%d",&M);
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%d %d",&D[i].x,&D[i].y);
    }
    fscanf(f,"%d",&ad);
    for(j=1;j<=M;j++)
    {
        for(i=1;i<=N;i++)
        {

                    dist=max(abs(D[j].x-A[ad].x),abs(D[j].y-A[ad].y))+max(abs(D[j].x-A[i].x),abs(D[j].y-A[i].y));
                    if(dist<minim)
                        {minim=dist;x=j;y=i;}
        }
    }
    fprintf(g,"%d\n%d",x,y);
    fclose(f);
    fclose(g);
    return 0;
}
