#include <cstdio>
#include <algorithm>
#include <cmath>
#define x second
#define y first
using namespace std;
int N;
pair<double,double> Y[100005];
pair<double,double> V[100005];
double dist(pair<double,double> a,pair<double,double> b)
{
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
double solve(int st,int dr)
{
    if(st==dr)return 1<<30;
    if(st==dr-1)
    {
        if(Y[st]>Y[dr])swap(Y[st],Y[dr]);
        return dist(Y[st],Y[dr]);
    }
    int mid=(st+dr)/2;
    double rez=min(solve(st,mid),solve(mid+1,dr));
    merge(Y+st,Y+mid+1,Y+mid+1,Y+1+dr,V+1);
    copy(V+1,V+(dr-st)+2,Y+st);
    int ind=0;
    for(int i=st;i<=dr;i++)if(abs(Y[mid].x-Y[i].x)<=rez)V[++ind]=Y[i];
    for(int i=1;i<ind;i++)
        for(int j=i+1;j<=i+7&&j<=ind;j++)
            rez=min(rez,dist(V[i],V[j]));
    return rez;
}
bool cmp(pair<double,double> a,pair<double,double> b)
{
    if(a.x!=b.x)return a.x<b.x;
    return a.y<b.y;
}
int main()
{
    scanf("%d\n",&N);
    for(int i=1;i<=N;i++)scanf("%lf %lf",&Y[i].x,&Y[i].y);
    sort(Y+1,Y+1+N,cmp);
    printf("%.2f",sqrt(solve(1,N)));
    return 0;
}
