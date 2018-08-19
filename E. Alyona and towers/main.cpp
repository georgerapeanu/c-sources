#include <cstdio>
#include <algorithm>

using namespace std;
struct node
{
    int l,r,m;
}AINT[1200005];
int N,M;
long long V[400005];
int sign(int x)
{
    return !V[x] ? 0:(V[x]<0 ? 1:-1);
}
void compute(int nod,int st,int dr)
{
    AINT[nod].l=AINT[2*nod].l;
    AINT[nod].r=AINT[2*nod+1].r;
    AINT[nod].m=max(AINT[2*nod].m,AINT[2*nod+1].m);
    int mid=(st+dr)/2;
    if(!sign(mid)||!sign(mid+1)||sign(mid)<sign(mid+1))
    {
        ;
    }
    else
    {
        AINT[nod].m=max(AINT[nod].m,AINT[2*nod].r+AINT[2*nod+1].l);
        if(AINT[2*nod].l==mid-st+1)AINT[nod].l+=AINT[2*nod+1].l;
        if(AINT[2*nod+1].r==dr-mid)AINT[nod].r+=AINT[2*nod].r;
    }

}
void build(int nod,int st,int dr)
{
    if(st==dr)
    {
        AINT[nod].l=AINT[nod].r=AINT[nod].m=(V[st]!=0);
        return ;
    }
    int mid=(st+dr)/2;
    build(nod*2,st,mid);
    build(nod*2+1,mid+1,dr);
    compute(nod,st,dr);
}
void u(int nod,int st,int dr,int poz,int val)
{
    if(st==dr)
    {
        V[st]+=val;
        AINT[nod].l=AINT[nod].r=AINT[nod].m=(V[poz]!=0);
        return ;
    }
    int mid=(st+dr)/2;
    if(mid>=poz)u(nod*2,st,mid,poz,val);
    else                   u(nod*2+1,mid+1,dr,poz,val);
    compute(nod,st,dr);
}
int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;i++)scanf("%I64d",&V[i]);
    for(int i=1;i<N;i++)V[i]-=V[i+1];V[N]=0;
    if(N>1)build(1,1,N-1);
    scanf("%d",&M);
    while(M--)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        if(x!=1)u(1,1,N-1,x-1,-z);
        if(y!=N)u(1,1,N-1,y,z);
        printf("%d\n",max(AINT[1].m,max(AINT[1].l,AINT[1].r))+1);
    }
    return 0;
}
