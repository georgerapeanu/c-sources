#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <fstream>
#define x first
#define y second
using namespace std;
FILE *f=fopen("arie.in","r");
FILE *g=fopen("arie.out","w");
typedef pair<int,int> point;
point A[22],B[22];
int N,M,arie1,arie2;
double xm,ym;
typedef pair<double,double> afpoint;
vector<afpoint> V;
int det(point a,point b,point c)
{
    return a.x*b.y+b.x*c.y+c.x*a.y-a.x*c.y-b.x*a.y-c.x*b.y;
}
double arie(afpoint a,afpoint b,afpoint c)
{
    return abs(a.x*b.y+b.x*c.y+c.x*a.y-a.x*c.y-b.x*a.y-c.x*b.y)/2;
}
short orie(point a,point b,point c)
{
    int tmp=det(a,b,c);
    if(tmp==0)
        return 0;
    return tmp<0 ? -1:1;
}
bool intersect(point a,point b,point c,point d)
{
    if(orie(a,b,c)!=orie(a,b,d)&&orie(c,d,a)!=orie(c,d,b))
        return 1;
    if(orie(a,b,c)==orie(a,b,d)&&orie(c,d,a)==orie(c,d,b)&&orie(c,d,b)==0)
        return 1;
    return 0;
}
bool cmp(afpoint a,afpoint b)
{
    return atan2(a.y-ym,a.x-xm)<atan2(b.y-ym,b.x-xm);
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
        fscanf(f,"%d%d",&A[i].x,&A[i].y);
    fscanf(f,"%d",&M);
    for(int i=1;i<=M;i++)
        fscanf(f,"%d%d",&B[i].x,&B[i].y);
    for(int i=2;i<N;i++)
    {
        arie1+=abs(det(A[1],A[i],A[i+1]));
    }
    for(int i=2;i<M;i++)
    {
        arie2+=abs(det(B[1],B[i],B[i+1]));
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            if(intersect(A[i],A[i%N+1],B[j],B[j%M+1]))
            {
                int a,b,c,ap,bp,cp;
                a=A[i%N+1].y-A[i].y;
                b=A[i].x-A[i%N+1].x;
                c=A[i].y*A[i%N+1].x-A[i].x*A[i%N+1].y;
                ap=B[j%M+1].y-B[j].y;
                bp=B[j].x-B[j%M+1].x;
                cp=B[j].y*B[j%M+1].x-B[j].x*B[j%M+1].y;
                if(a*bp-ap*b!=0)
                {
                    double x=double(b*cp-bp*c)/(bp*a-b*ap);
                    double y=double(ap*c-a*cp)/(bp*a-b*ap);
                    V.push_back(make_pair(x,y));
                }
            }
        }
    }
    for(int i=1;i<=N;i++)
    {
        int tmp=0;
        for(int j=1;j<=M;j++)
        {
            tmp+=abs(det(A[i],B[j],B[j%M+1]));
        }
        if(arie2==tmp)
            V.push_back(A[i]);
    }
    for(int j=1;j<=M;j++)
    {
        int tmp=0;
        for(int i=1;i<=N;i++)
            tmp+=abs(det(B[j],A[i],A[i%N+1]));
        if(arie1==tmp)
            V.push_back(B[j]);
    }
    for(auto it:V)
    {
        xm+=(it).x;
        ym+=(it).y;
    }
    xm/=V.size();
    ym/=V.size();
    sort(V.begin(),V.end(),cmp);
    double rez=0;
    int len=V.size();
    for(int i=0;i<len;i++)
    {
        rez+=arie(make_pair(xm,ym),V[i],V[(i+1)%len]);
    }
    fprintf(g,"%.3f",rez);
    fclose(f);
    fclose(g);
    return 0;
}
