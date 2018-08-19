#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
FILE *f=fopen("cercuri4.in","r");
FILE *g=fopen("cercuri4.out","w");
typedef struct {int x,y,r,f;} cerc;
cerc V[3005];
long long dp[3005];
int N;
long long rez;
double dist(double x,double y,double xx,double yy)
{
    return sqrt(pow(xx-x,2)+pow(yy-y,2));
}
bool cmp(cerc a,cerc b)
{
    return a.r<b.r;
}
bool inclus(cerc a,cerc b)
{
    double d=dist((double)a.x,(double)a.y,(double)b.x,(double)b.y);
    return (d+a.r<=b.r);
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d%d%d%d",&V[i].x,&V[i].y,&V[i].r,&V[i].f);
    }
    sort(V+1,V+1+N,cmp);
    for(int i=1;i<=N;i++)
    {
        dp[i]=V[i].f;
        for(int j=1;j<i;j++)
        {
            if(inclus(V[j],V[i]))
                dp[i]=max(dp[i],dp[j]+V[i].f);
        }
        rez=max(rez,dp[i]);
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
