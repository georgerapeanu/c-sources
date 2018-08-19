#include <cstdio>
#include <algorithm>
#define NMAX 200000
#define mid(x,y) (x+y)/2
using namespace std;
FILE *f=fopen("maxq.in","r");
FILE *g=fopen("maxq.out","w");
typedef struct{long long prefix,sufix,sumatotala,sumamaxima;} data;
int N,op,a,b;
data A[4*NMAX+5];
int M;
void update(int nod,int st,int dr,int poz,int val)
{
    if(st==dr)
    {
        A[nod].prefix=A[nod].sufix=A[nod].sumatotala=A[nod].sumamaxima=val;
        return ;
    }
    if(mid(st,dr)>=poz) update(nod*2,st,mid(st,dr),poz,val);
    else update(nod*2+1,mid(st,dr)+1,dr,poz,val);
    A[nod].prefix=max(A[2*nod].prefix,A[2*nod].sumatotala+A[2*nod+1].prefix);
    A[nod].sufix=max(A[2*nod+1].sufix,A[2*nod+1].sumatotala+A[2*nod].sufix);
    A[nod].sumatotala=A[2*nod].sumatotala+A[2*nod+1].sumatotala;
    A[nod].sumamaxima=max(max(A[2*nod].sumamaxima,A[2*nod+1].sumamaxima),A[2*nod].sufix+A[2*nod+1].prefix);
}
data querry(int nod,int st,int dr,int X,int Y)
{
    if(X<=st&&Y>=dr) return A[nod];
    if(mid(st,dr)>=Y) return querry(nod*2,st,mid(st,dr),X,Y);
    if(mid(st,dr)<X) return querry(nod*2+1,mid(st,dr)+1,dr,X,Y);
    data a=querry(2*nod,st,mid(st,dr),X,Y);
    data b=querry(2*nod+1,mid(st,dr)+1,dr,X,Y);
    data c;
    c.prefix=max(a.prefix,a.sumatotala+b.prefix);
    c.sufix=max(b.sufix,b.sumatotala+a.sufix);
    c.sumatotala=a.sumatotala+b.sumatotala;
    c.sumamaxima=max(max(a.sumamaxima,b.sumamaxima),a.sufix+b.prefix);
    return c;
}
void build(int nod,int st,int dr)
{
    if(st==dr)
    {
        fscanf(f,"%lld",&A[nod].prefix);A[nod].sufix=A[nod].sumatotala=A[nod].sumamaxima=A[nod].prefix;return ;
    }
    build(nod*2,st,mid(st,dr));
    build(nod*2+1,mid(st,dr)+1,dr);
    A[nod].prefix=max(A[2*nod].prefix,A[2*nod].sumatotala+A[2*nod+1].prefix);
    A[nod].sufix=max(A[2*nod+1].sufix,A[2*nod+1].sumatotala+A[2*nod].sufix);
    A[nod].sumatotala=A[2*nod].sumatotala+A[2*nod+1].sumatotala;
    A[nod].sumamaxima=max(max(A[2*nod].sumamaxima,A[2*nod+1].sumamaxima),A[2*nod].sufix+A[2*nod+1].prefix);
}
int main()
{
    fscanf(f,"%d",&N);
    build(1,1,N);
    fscanf(f,"%d",&M);
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d%d%d",&op,&a,&b);
        if(!op) update(1,1,N,a+1,b);
        else fprintf(g,"%lld\n",max(0LL,querry(1,1,N,a+1,b+1).sumamaxima));
    }
    fclose(f);
    fclose(g);
    return 0;
}
