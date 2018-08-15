#include <algorithm>
#include <cstdio>
using namespace std;
FILE *f=fopen("arbint.in","r");
FILE *g=fopen("arbint.out","w");
int N,M;
int val,op,a,b,poz,X,Y;
int A[400005];
void update(int nod,int st,int dr)
{
    if(st==dr)  {A[nod]=val;return;}
    int mid=(st+dr)/2;
    if(poz<=mid)
    {
        update(2*nod,st,mid);
    }
    else
    {
        update(2*nod+1,mid+1,dr);
    }
    A[nod]=max(A[2*nod],A[2*nod+1]);
}
int query(int nod,int st,int dr)
{
    if(X<=st&&dr<=Y)
        return A[nod];
    int mid=(st+dr)/2;
    if(mid>=Y)  return query(2*nod,st,mid);
    else if(mid<X) return query(2*nod+1,mid+1,dr);
    else return max(query(2*nod,st,mid),query(2*nod+1,mid+1,dr));
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        poz=i;
        update(1,1,N);
    }
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d%d%d",&op,&a,&b);
        poz=a;val=b;
        X=a;Y=b;
        if(!op)
            fprintf(g,"%d\n",query(1,1,N));
        else
            update(1,1,N);
    }
    fclose(f);
    fclose(g);
    return 0;
}
