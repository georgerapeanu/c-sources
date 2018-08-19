#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("simetrii.in","r");
FILE *g=fopen("simetrii.out","w");
struct point {int x,y;};
point A[100005];
point B[100005];
int N;
void rot90()
{
    for(int i=1;i<=N;i++)
    {
        point tmp=A[i];
        A[i].x=-tmp.y;
        A[i].y=tmp.x;
    }
}
bool cmp(point a,point b)
{
    if(a.x!=b.x)
        return a.x<b.x;
    return a.y<b.y;
}
point ok()
{
    sort(A+1,A+1+N,cmp);
    point rez={B[1].x-A[1].x,B[1].y-A[1].y};
    for(int i=2;i<=N;i++)
    {
        if(B[i].x-A[i].x!=rez.x||B[i].y-A[i].y!=rez.y)
            return {-100001,-100001};
    }
    return rez;
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d %d",&A[i].x,&A[i].y);
    }
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d %d",&B[i].x,&B[i].y);
    }
    sort(B+1,B+1+N,cmp);
    for(int i=0;i<=3;i++)
    {
        point rez=ok();
        if(rez.x!=-100001)
        {
            fprintf(g,"2\n1 0 0 %d\n",i*90);
            fprintf(g,"0 %d %d\n",rez.x,rez.y);
            return 0;
        }
        rot90();
    }
    fprintf(g,"-1");
    fclose(f);
    fclose(g);
    return 0;
}
