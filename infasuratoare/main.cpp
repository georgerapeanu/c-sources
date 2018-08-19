#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#define x first
#define y second
using namespace std;
FILE *f=fopen("infasuratoare.in","r");
FILE *g=fopen("infasuratoare.out","w");
int N;
typedef pair<double,double> POINT;
POINT V[120005];
int st[120005];
double det(POINT a,POINT b,POINT c)
{
    return a.x*b.y-a.x*c.y+b.x*c.y-b.x*a.y+c.x*a.y-c.x*b.y;
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%lf %lf",&V[i].x,&V[i].y);
    }
    sort(V+1,V+1+N);
    st[++st[0]]=1;
    st[++st[0]]=2;
    for(int i=3;i<=N;i++)
    {
        while(st[0]>1&&det(V[st[st[0]-1]],V[st[st[0]]],V[i])<0)st[0]--;
        st[++st[0]]=i;
    }
    for(int i=N-1;i;i--)
    {
        while(st[0]>1&&det(V[st[st[0]-1]],V[st[st[0]]],V[i])<0)st[0]--;
        st[++st[0]]=i;
    }
    fprintf(g,"%d\n",st[0]-1);
    for(int i=1;i<st[0];i++)fprintf(g,"%.6f %.6f\n",V[st[i]].x,V[st[i]].y);
    fclose(f);
    fclose(g);
    return 0;
}
