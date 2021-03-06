#include <cstdio>
#include <cmath>
#define PI 3.14159265
using namespace std;
typedef struct{double x;double y;} POINT;
FILE *f=fopen("texan.in","r"),*g=fopen("texan.out","w");
POINT P[510],R[510],A,B,C;
int n,i,j;
POINT rotire(POINT A,POINT B,double u)
{
    POINT R,P;
    R.x=B.x-A.x;
    R.y=B.y-A.y;
    P.x=cos(u)*R.x-sin(u)*R.y;
    P.y=cos(u)*R.y+sin(u)*R.x;
    P.x+=A.x;
    P.y+A.y;
    return P;
}
bool intersectie(POINT A,POINT B,POINT C,POINT D,POINT &E)
{
    double a=0,b=0,c=0,d=0,x,y;
    if(A.x==B.x&&C.x!=D.x)
    {
        x=A.x;
        c=(D.y-C.y)/(D.x-C.x);
        d=-1*(C.x)*(D.y-C.y)/(D.x-C.x)+C.y;
        y=c*x+d;
        E.x=x;
        E.y=y;
        return 1;
    }
    else if(A.x!=B.x&&C.x==D.x)
    {
        x=C.x;
        a=(B.y-A.y)/(B.x-A.x);
        b=-1*(A.x)*(B.y-A.y)/(B.x-A.x)+A.y;
        y=a*x+b;
        E.x=x;
        E.y=y;
        return 1;
    }
    else if(A.x==B.x&&C.x==D.x)
        return 0;
    else
    {
        a=(B.y-A.y)/(B.x-A.x);
        b=-1*(A.x)*(B.y-A.y)/(B.x-A.x)+A.y;
        c=(D.y-C.y)/(D.x-C.x);
        d=-1*(C.x)*(D.y-C.y)/(D.x-C.x)+C.y;
        if(a==c)
        return 0;
        x=(d-b)/(a-c);
        y=a*x+b;
        if(((A.x<=x&&x<=B.x)||(B.x<=x&&x<=A.x))&&((A.y<=y&&y<=B.y)||(B.y<=y&&y<=A.y)))
        {
            E.x=x;
            E.y=y;
            return 1;
        }
        return 0;
    }
}
int main()
{
    fscanf(f,"%d",&n);
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%lf %lf",&P[i].x,&P[i].y);
    }
    P[n+1].y=P[1].y;
    P[n+1].x=P[1].x;
    A.x=(P[1].x+P[2].x)/2;
    A.y=(P[1].y+P[2].y)/2;
    for(i=1;i<=n+1;i++)
    {
        R[i]=rotire(A,P[i],PI/3.00);
    }
    for(i=1;i<=n&&B.x==0&&B.y==0;i++)
    {
        for(j=1;j<=n&&B.x==0&&B.y==0;j++)
        {
            if(intersectie(P[i],P[i+1],R[j],R[j+1],B)==1&&(B.x!=A.x||B.y!=A.y))
            {
                ;
            }
            else
            {
                B.x=0;
                B.y=0;
            }
        }
    }
    for(i=1;i<=n+1;i++)
    {
        R[i]=rotire(A,P[i],-PI/3.00);
    }
        for(i=1;i<=n&&C.x==0&&C.y==0;i++)
    {
        for(j=1;j<=n&&C.x==0&&C.y==0;j++)
        {
            if(intersectie(P[i],P[i+1],R[j],R[j+1],C)==1&&(C.x!=A.x||C.y!=A.y))
            {
                ;
            }
            else
            {
                C.x=0;
                C.y=0;
            }
        }
    }
    fprintf(g,"%lf %lf\n%lf %lf\n%lf %lf\n",A.x,A.y,B.x,B.y,C.x,C.y);
    fclose(f);
    fclose(g);
    return 0;
}
