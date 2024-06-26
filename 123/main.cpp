#include <cstdio>
#include <cmath>
#include <algorithm>
#define inf 100005
using namespace std;
FILE *f=fopen("123.in","r");
FILE *g=fopen("123.out","w");
int N,V[10005],i,j,K,P,nr,best;
char c[10005];
struct {int x,y,z;} info[10005];
bool ok()
{
    int a1,a2,a3;
    a1=info[i].x-info[j].x;
    a2=info[i].y-info[j].y;
    a3=info[i].z-info[j].z;
    if(!a1||!a2||abs(a1-a2)<=P)
        if(!a1||!a3||abs(a1-a3)<=P)
            if(!a2||!a3||abs(a2-a3)<=P)
                return true;
    return false;
}
int main()
{
    fscanf(f,"%d %d %d\n",&N,&K,&P);
    fgets(c+1,10005,f);
    V[1]=1;
    for(i=1;i<=N;i++)
        info[i]={info[i-1].x+(c[i]=='1'),info[i-1].y+(c[i]=='2'),info[i-1].z+(c[i]=='3')};
    for(i=2;i<=N;i++)
    {
        nr=max(0,i-K);
        best=V[i-1];
        for(j=i-2;j>=nr;j--)
        {
            if(ok())
            {
                best=min(V[j],best);
            }
        }
        V[i]=1+best;
    }
    fprintf(g,"%d",V[N]);
    return 0;
}
