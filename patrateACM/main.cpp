#include <cstdio>
#include <algorithm>
#define inf 1000000005
using namespace std;
FILE *f=fopen("patrate.in","r");
FILE *g=fopen("patrate.out","w");
typedef struct{int x,y,l;} patrat;
typedef struct{int X1,Y1,X2,Y2;} dreptunghi;
typedef struct{int x,y;} punct;
punct V[100005];
int N;
patrat p1,p2,p3;
dreptunghi d1,d2,d3;
bool inside(patrat p,punct x)
{
        return p.x<=x.x&&x.x<=p.x+p.l&&p.y<=x.y&&x.y<=p.y+p.l;
}
bool get3(int l)
{
    d3={inf,inf,-inf,-inf};
    for(int i=1;i<=N;i++)
    {
        if(!inside(p1,V[i])&&!inside(p2,V[i]))
        {
            d3.X1=min(d3.X1,V[i].x);
            d3.Y1=min(d3.Y1,V[i].y);
            d3.X2=max(d3.X2,V[i].x);
            d3.Y2=max(d3.Y2,V[i].y);
        }
    }
    if(d3.X2-d3.X1<=l&&d3.Y2-d3.Y1<=l)
        return 1;
    return 0;
}
bool get2(int l)
{
    d2={inf,inf,-inf,-inf};
    for(int i=1;i<=N;i++)
    {
        if(!inside(p1,V[i]))
        {
            d2.X1=min(d2.X1,V[i].x);
            d2.Y1=min(d2.Y1,V[i].y);
            d2.X2=max(d2.X2,V[i].x);
            d2.Y2=max(d2.Y2,V[i].y);
        }
    }
    p2={d2.X1,d2.Y1,l};
    if(get3(l))
        return 1;
    p2={d2.X2-l,d2.Y1,l};
    if(get3(l))
        return 1;
    ///p2={d2.X1,d2.Y2-l,l};
   /// if(get3(l))
   ///     return 1;
  ///  p2={d2.X2-l,d2.Y2-l,l};
  ///  if(get3(l))
  ///      return 1;
    return 0;
}
bool ok(int l)
{
    p1=p2=p3={-1,-1,-1};
    p1={d1.X1,d1.Y1,l};
    if(get2(l))
        return 1;
    p1={d1.X1,d1.Y2-l,l};
    if(get2(l))
        return 1;
    p1={d1.X2-l,d1.Y1,l};
    if(get2(l))
        return 1;
    p1={d1.X2-l,d1.Y2-l,l};
    if(get2(l))
        return 1;
    return 0;
}
int main()
{
    d1={inf,inf,-inf,-inf};
   /// fscanf(f,"%d",&N);
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
    {
        ///fscanf(f,"%d %d",&V[i].x,&V[i].y);
        scanf("%d %d",&V[i].x,&V[i].y);
        d1.X1=min(d1.X1,V[i].x);
        d1.Y1=min(d1.Y1,V[i].y);
        d1.X2=max(d1.X2,V[i].x);
        d1.Y2=max(d1.Y2,V[i].y);
    }
    int st=0,dr=max(d1.X2-d1.X1,d1.Y2-d1.Y1),mid;
    while(st<dr)
    {
        mid=(st+dr)/2;
        if(ok(mid))
        {
            dr=mid;
        }
        else
            st=mid+1;
    }
    ///fprintf(g,"%d",st);
    printf("%d",st);
    fclose(f);
    fclose(g);
    return 0;
}
