#include <cstdio>
#include <cmath>
#include <algorithm>
#define x first.first
#define y first.second
#define ind second
using namespace std;
FILE *f=fopen("melc.in","r");
FILE *g=fopen("melc.out","w");
int N;
double X,Y;
typedef pair<pair<double,double>,int> point;
point V[1005];
int poz;
bool cmp(point a,point b)
{
    return atan2(a.y,a.x)<atan2(b.y,b.x);
}
int main()
{
    fscanf(f,"%lf%lf",&X,&Y);
    fscanf(f,"%d",&N);
    for(int i=0;i<N;i++)
    {
        fscanf(f,"%lf%lf%d",&V[i].x,&V[i].y,&V[i].ind);
        V[i].x-=X;
        V[i].y-=Y;
    }
    sort(V,V+N,cmp);
    for(int i=0;i<N;i++)
    {
        if(atan2(V[(i+1)%N].y,V[(i+1)%N].x)-atan2(V[i].y,V[i].x)>acos(-1))
            poz=(i+1)%N;
    }
    fprintf(g,"0\n");
    for(int i=0;i<N;i++)
        fprintf(g,"%d\n",V[(i+poz)%N].ind);
    fprintf(g,"0\n");
    fclose(f);
    fclose(g);
    return 0;
}
