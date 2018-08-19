#include <cstdio>
#include <algorithm>
#include <fstream>
#define x first
#define y second
using namespace std;
FILE *f=fopen("dreapta.in","r");
FILE *g=fopen("dreapta.out","w");
typedef pair <double,double> POINT;
POINT V[100005];
POINT D[100005];
POINT E[100005],*p;
double a,b,c;
double ap,bp,cp,minx,miny,maxx,maxy;
int N,i,Q,K;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
        fscanf(f,"%lf %lf",&V[i].x,&V[i].y);
    fscanf(f,"%d",&Q);
    for(i=1;i<=Q;i++)
    {
        fscanf(f,"%lf %lf",&D[i].x,&D[i].y);
    }
    a=D[2].y-D[1].y;
    b=D[1].x-D[2].x;
    c=D[1].y*D[2].x-D[1].x*D[2].y;
    for(i=1;i<=N;i++)
    {
        ap=V[i%N+1].y-V[i].y;
        bp=V[i].x-V[i%N+1].x;
        cp=V[i].y*V[i%N+1].x-V[i].x*V[i%N+1].y;
        E[++K]={(-(bp*c-b*cp))/(a*bp-ap*b),(a*cp-ap*c)/(ap*b-a*bp)};
        if(V[i].x<V[i%N+1].x)
        {
            minx=V[i].x;
            maxx=V[i%N+1].x;
        }
        else
        {
            maxx=V[i].x;
            minx=V[i%N+1].x;
        }
        if(V[i].y<V[i%N+1].y)
        {
            miny=V[i].y;
            maxy=V[i%N+1].y;
        }
        else
        {
            maxy=V[i].y;
            miny=V[i%N+1].y;
        }
        if(!(minx<=E[K].x&&E[K].x<=maxx&&miny<=E[K].y&&E[K].y<=maxy))
            K--;
    }
    sort(E+1,E+1+K);
    for(i=1;i<=Q;i++)
    {
        p=lower_bound(E+1,E+1+K,D[i]);
        fprintf(g,"%d\n",(p-E-1)%2);
    }
    fclose(f);
    fclose(g);
    return 0;
}
