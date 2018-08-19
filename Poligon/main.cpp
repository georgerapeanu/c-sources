#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
FILE *f=fopen("poligon.in","r");
FILE *g=fopen("poligon.out","w");
vector<int> V[60005];
struct punct{
    int x,y;
    punct()
    {
        x=y=0;
    }
    punct(int a,int b)
    {
        x=a;
        y=b;
    }
};
struct dreapta
{
    int a,b;
    long long c;
    dreapta()
    {
        ;
    }
    dreapta(punct A,punct B)
    {
        a=B.y-A.y;
        b=A.x-B.x;
        c=1LL*B.x*A.y-1LL*A.x*B.y;
    }
};
punct P[60005];
dreapta V[60005];
int N,M;
int x[60005];
int nx;
vector<dreapta> strip[60005];
set<punct> segm[60005];
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d%d",&P[i].x,&P[i].y);
        x[i]=P[i].x;
    }
    sort(x+1,x+1+N);
    x[0]=-1;
    for(int i=1;i<=N;i++)
    {
        if(x[nx]!=x[i])
            x[++nx]=x[i];
        V[i]=dreapta(P[i],P[i%N+1]);
    }
    for(int i=1;i<=nx;i++)
    {
        stx[i]=0;drx[i]=-1;
        for(int j=1;j<=N;j++)
        {
            if(V[j].b==0)
            {
                if(P[j].x==x[i]) {segm[i].insert(P[j].y);segm[i].insert(P[j%N+1].y);}
                continue;
            }
            if(det(P[j],{x[i],0},{x[i],1})*det(P[j%N+1],{x[i],0},{x[i],1}))
                strip[i].push_back(V[j]);
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
