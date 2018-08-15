#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("dist2.in","r");
FILE *g=fopen("dist2.out","w");
struct punct
{
    int x,y;
    bool operator < (const punct &other)const
    {
        if(x!=other.x)return x<other.x;
        return y<other.y;
    }
}V[100005];
int N;
bool ok(int d)
{
    int ymax=0,ymin=2e6;
    for(int r=1,l=0;r<=N;r++)
    {
        while(V[l+1].x<=V[r].x-d)
        {
            l++;
            ymax=max(ymax,V[l].y);
            ymin=min(ymin,V[l].y);
        }
        if(ymax>=V[r].y+d||ymin<=V[r].y-d)return 1;
    }
    return 0;
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d %d",&V[i].x,&V[i].y);
    }
    sort(V+1,V+1+N);
    int st=1,dr=2000001;
    while(dr-st>1)
    {
        int mid=(st+dr)/2;
        if(ok(mid))st=mid;
        else dr=mid;
    }
    fprintf(g,"%d",st);
    fclose(f);
    fclose(g);
    return 0;
}
