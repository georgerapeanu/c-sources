#include <cstdio>
#include <algorithm>
#define x first.first
#define y first.second
#define nod second
using namespace std;
FILE *f=fopen("banana.in","r");
FILE *g=fopen("banana.out","w");
int N,K;
pair<pair<int,int>,int> V[16006];
int T[16006];
int fi(int nod)
{
    if(T[nod]<0)return nod;
    return T[nod]=fi(T[nod]);
}
void u(int X,int Y)
{
    X=fi(X);
    Y=fi(Y);
    if(X==Y)return ;
    if(T[X]<T[Y]){T[X]+=T[Y];T[Y]=X;}
    else         {T[Y]+=T[X];T[X]=Y;}
}
bool cmp1(pair<pair<int,int>,int> a,pair<pair<int,int>,int> b)
{
    if(a.x!=b.x)return a.x<b.x;
    return a.y<b.y;
}
bool cmp2(pair<pair<int,int>,int> a,pair<pair<int,int>,int> b)
{
    if(a.y!=b.y)return a.y<b.y;
    return a.x<b.x;
}
int main()
{
    fscanf(f,"%d %d",&N,&K);
    for(int i=1;i<=N;i++)T[i]=-1;
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d %d",&V[i].x,&V[i].y);V[i].nod=i;
    }
    sort(V+1,V+1+N,cmp1);
    for(int i=2;i<=N;i++)
    {
        if(V[i].x==V[i-1].x&&V[i].y==V[i-1].y+1)u(V[i].nod,V[i-1].nod);
    }
    sort(V+1,V+1+N,cmp2);
    for(int i=2;i<=N;i++)
    {
        if(V[i].y==V[i-1].y&&V[i].x==V[i-1].x+1)u(V[i].nod,V[i-1].nod);
    }
    sort(T+1,T+1+N);
    int rez=0;
    for(int i=1;i<=K;i++)rez-=T[i];
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
