#include <cstdio>
#include <fstream>
#include <cmath>
#define PI 3.14159265
using namespace std;
FILE *f=fopen("patrate.in","r");
FILE *g=fopen("patrate.out","w");
bool B[51][51];
int x,N,rez,dx,dy,i,j;
pair <int,int> a,b,c,d;
int y;
/*typedef struct {double x,y;} POINT;
typedef struct {double a,b,c;} DREAPTA;
double magnitude(POINT a,POINT b)
{
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}
DREAPTA detdreapta(POINT a,POINT b)
{
    DREAPTA D;
    D.a=b.y-a.y;
    D.b=a.x-b.x;
    D.c=b.x*a.y-a.x*b.y;
    return D;
}
POINT rotunj(POINT x)
{
    if(x.x-int(x.x)<=0.00000001)
    {
        x.x=int(x.x);
    }
    else if(int(x.x)+1-x.x<=0.00000001)
    {
        x.x=int(x.x)+1;
    }
    if(x.y-int(x.y)<=0.00000001)
    {
        x.y=int(x.y);
    }
    else if(int(x.y)+1-x.y<=0.00000001)
    {
        x.y=int(x.y)+1;
    }
    return x;
}
bool valid(POINT a,POINT b)
{
    double R;
    R=magnitude(a,b)/2;
    POINT mid={(a.x+b.x)/2,(a.y+b.y)/2};
    mid.x=mid.x;
    mid.y=mid.y;
    double md,dg;
    md=atan((a.y-b.y)/(a.x-b.x))*(180/PI);
    if(md<0)
        md+=180;
    dg=180-md;
    dg=90-dg;
    double devx,devy;
    devy=sin(dg*PI/180)*R;
    devx=cos(dg*PI/180)*R;
    POINT c,d;
    c={mid.x+devx,mid.y+devy};
    d={mid.x-devx,mid.y-devy};
    if((c.x>0&&c.y>0)||(0-c.x<=0.00000001&&0-c.y<=0.00000001))
        c=rotunj(c);
    if((d.x>0&&d.y>0)||(0-d.x<=0.00000001&&0-d.y<=0.00000001))
        d=rotunj(d);
    if(c.x==int(c.x)&&c.y==int(c.y)&&d.x==int(d.x)&&d.y==int(d.y))
    {
        if(B[N-(int)a.y][(int)a.x+1]==B[N-(int)b.y][(int)b.x+1]&&B[N-(int)b.y][(int)b.x+1]==B[N-(int)c.y][(int)c.x+1]&&B[N-(int)c.y][(int)c.x+1]==B[N-(int)d.y][(int)d.x+1])
            return 1;
    }
    return 0;
}*/
void fix(pair<int,int> &x)
{
    x.second=N-x.second+1;
    swap(x.first,x.second);
}
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
        for(j=1;j<=N;j++)
            fscanf(f,"%d",&B[i][j]);
    for(x=1;x<=N;x++)
    {
        for(y=1;y<=N;y++)
        {
            for(dx=1;dx<=N-x;dx++)
            {
                for(dy=0;dy<=N-y;dy++)
                {
                    if(y+dy+dx<=N&&x+dx-dy>0&&x-dy>0&&y+dx>0)
                    {
                        a=make_pair(x,y);
                        b=make_pair(x+dx,y+dy);
                        c=make_pair(x+dx-dy,y+dy+dx);
                        d=make_pair(x-dy,y+dx);
                        fix(a);
                        fix(b);
                        fix(c);
                        fix(d);
                        if(B[a.first][a.second]==B[b.first][b.second]&&B[b.first][b.second]==B[c.first][c.second]&&B[c.first][c.second]==B[d.first][d.second])
                            rez++;
                    }
                }
            }
        }
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
