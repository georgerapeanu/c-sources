#include <cstdio>
using namespace std;
FILE *f=fopen("grindina.in","r");
FILE *g=fopen("grindina.out","w");
short frecv[101],i,j,N,G,nrp,next,maxim;
double x,y,nx;
typedef struct {double x,y;} punct;
short a[105];
short b[105];
punct V[101][101];
bool inside(int poligon,double x,double y)
{
    int nr=0;
    for(int i=1;i<=V[poligon][0].x;i++)
    {
        next=(i)%(int(V[poligon][0].x))+1;
        double x1=V[poligon][i].x;
        double y1=V[poligon][i].y;
        double y2=V[poligon][next].y;
        double x2=V[poligon][next].x;
        if(y2-y1!=0)
        {
            nx=(((x2-x1)*(y-y1))/(y2-y1))+x1;
            if(((x1<=nx&&nx<=x2)||(x2<=nx&&nx<=x1))&&((y1<=y&&y<=y2)||(y2<=y&&y<=y1)))
            {
                if(nx<x)
                {
                    if(y1==y||y2==y)
                        {
                            if(y1==y&&y1>y2)
                                nr++;
                            else if(y2==y&&y2>y1)
                                nr++;
                        }
                    else
                        nr++;
                }
                else if(nx==x)
                    return 0;
            }
        }
    }
    return nr%2;
}
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&nrp);
        V[i][0].x=nrp;
        for(j=1;j<=nrp;j++)
        {
            fscanf(f,"%lf %lf",&V[i][j].x,&V[i][j].y);
        }
    }
    fscanf(f,"%d",&G);
    for(i=1;i<=G;i++)
    {
        fscanf(f,"%lf %lf",&x,&y);
        for(j=1;j<=N;j++)
        {
            if(inside(j,x,y))
                {frecv[j]++;}
        }
    }
    for(i=1;i<=N;i++)
    {
        if(frecv[i]==0)
            b[++b[0]]=i;
        if(frecv[i]>maxim)
        {
            a[0]=0;
            maxim=frecv[i];
        }
        if(frecv[i]==maxim)
            a[++a[0]]=i;
    }
    fprintf(g,"%d\n",a[0]);
    for(i=1;i<=a[0];i++)
    {
        fprintf(g,"%d ",a[i]);
    }
    fprintf(g,"\n%d\n",b[0]);
    if(!b[0])
        fprintf(g,"0");
    for(i=1;i<=b[0];i++)
    {
        fprintf(g,"%d ",b[i]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
