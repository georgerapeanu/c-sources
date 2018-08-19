#include <cstdio>
#include <iostream>
#define x first
#define fp first
#define y second
#define sp second
using namespace std;
FILE *f=fopen("geometry.in","r");
FILE *g=fopen("geometry.out","w");
typedef pair<int,int> point;
typedef pair<point,point> segm;
segm V[505];
int N;
int nr;
int det(point a,point b,point c)
{
    int v=a.x*b.y+b.x*c.y+c.x*a.y-a.x*c.y-b.x*a.y-c.x*b.y;
    if(v<0) return -1;
    if(v>0) return 1;
    return 0;
}
bool intre(point a,point b,point c)
{
    return max(a.x,b.x)>=c.x&&c.x>=min(a.x,b.x)&&max(a.y,b.y)>=c.y&&c.y>=min(a.y,b.y);
}
bool interseceaza(segm a,segm b)
{
    int d,e,f,g;
    d=det(a.fp,a.sp,b.fp);
    e=det(a.fp,a.sp,b.sp);
    f=det(b.fp,b.sp,a.fp);
    g=det(b.fp,b.sp,a.sp);
    if(d*e<0&&f*g<0)
        return 1;
    if(!d&&intre(a.fp,a.sp,b.fp))
        return 1;
    if(!e&&intre(a.fp,a.sp,b.sp))
        return 1;
    if(!f&&intre(b.fp,b.sp,a.fp))
        return 1;
    if(!g&&intre(b.fp,b.sp,a.sp))
        return 1;
    return 0;
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
        fscanf(f,"%d%d%d%d",&V[i].fp.x,&V[i].fp.y,&V[i].sp.x,&V[i].sp.y);
    for(int i=1;i<=N;i++)
        for(int j=i+1;j<=N;j++)
            nr+=interseceaza(V[i],V[j]);
    fprintf(g,"%d",nr);
    fclose(f);
    fclose(g);
    return 0;
}
