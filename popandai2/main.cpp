#include <cstdio>
#include <cmath>
#include <algorithm>
#include <fstream>
#define x first
#define y second
using namespace std;
FILE *f=fopen("popandai2.in","r");
FILE *g=fopen("popandai2.out","w");
typedef pair<int,int> point;
point V[1005];
int N,urm[1005],ant[1005];
int B[1005][1005];
int rez;
int arie(point a,point b,point c)
{
    return abs(a.x*b.y+b.x*c.y+c.x*a.y-a.x*c.y-b.x*a.y-c.x*b.y);
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d%d",&V[i].x,&V[i].y);
        urm[i]=i+1;
        ant[i]=i-1;
    }
    ant[1]=N;
    urm[N]=1;
    for(int i=1;i<=N;i++)
    {
        int k=urm[i];
        for(int j=urm[urm[i]];j!=ant[i];j=urm[j])
        {
            while(arie(V[i],V[k],V[j])<arie(V[i],V[urm[k]],V[j]))
                k=urm[k];
            B[i][j]+=arie(V[i],V[k],V[j]);
        }
        k=ant[i];
        for(int j=ant[ant[i]];j!=urm[i];j=ant[j])
        {
            while(arie(V[i],V[k],V[j])<arie(V[i],V[ant[k]],V[j]))
                k=ant[k];
            B[i][j]+=arie(V[i],V[k],V[j]);
            rez=max(rez,B[i][j]);
        }
    }
    fprintf(g,"%d.%d",rez/2,(rez&1)*5);
    fclose(f);
    fclose(g);
    return 0;
}
