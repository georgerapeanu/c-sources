#include <cstdio>
#include <cmath>
#include <algorithm>
#define x first
#define y second
#define tp double
using namespace std;
FILE *f=fopen("taie.in","r");
FILE *g=fopen("taie.out","w");
typedef pair<tp,tp> punct;
typedef pair<punct,punct> dreapta;
double alfa=1e-4;
int N;
int nr=0;
punct A[1005];
punct B[1005];
punct a,b;
punct rez={0,20000},tmp;
tp det(punct a,punct b,punct c)
{
    int val=a.x*b.y+b.x*c.y+c.x*a.y-a.x*c.y-b.x*a.y-c.x*b.y;
    if(val==0)return 0;
    if(val<0)return -1;
    return 1;
}
bool inter(punct a,punct b,punct c,punct d)
{
    tp e,f;
    e=det(c,d,a);
    f=det(c,d,b);
    if(e*f<=0)return 1;
    return 0;
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%lf%lf%lf%lf",&A[i].x,&A[i].y,&B[i].x,&B[i].y);
        if(A[i]>B[i])
            swap(A[i],B[i]);
    }
    b={1000000,1000000};
    a={-b.x,-b.y};
    for(int i=1;i<=N;i++)
    {
        a.x=max(a.x,A[i].x);
        a.y=max(a.y,A[i].y);
        b.x=min(b.x,B[i].x);
        b.y=min(b.y,B[i].y);
    }
    int nr=0;
    for(int i=1;i<=N;i++)
    {
        if(inter(A[i],B[i],a,b))
            nr++;
    }
    if(nr<N)fprintf(g,"-1");
    else fprintf(g,"%.10f %.10f %.10f %.10f",a.x,a.y,b.x,b.y);
    fclose(f);
    fclose(g);
    return 0;
}
