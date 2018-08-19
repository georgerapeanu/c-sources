#include <iostream>
#include <algorithm>
using namespace std;
int AIB[100005];
int N;
int V[100005];
int A[100005];
int AINT[400005];
void u(int p,int v)
{
    for(;p<=N;p+=(-p)&p)
        AIB[p]+=v;
}
int q(int p)
{
    int s=0;
    for(;p;p-=(-p)&p)
    {
        s+=AIB[p];
    }
    return s;
}
void u(int nod,int st,int dr,int val,int poz)
{
    if(st==dr)
    {
        AINT[nod]=val;
        return;
    }
    int mid=(st+dr)/2;
    if(st<=poz&&poz<=mid)u(2*nod,st,mid,val,poz);
    else u(2*nod+1,mid+1,dr,val,poz);
    AINT[nod]=min(AINT[2*nod],AINT[2*nod+1]);
}
int unde(int nod,int st,int dr,int val,int S,int D)
{
    if(S==D)
    {
        if(val==AINT[nod])return S;
        else return -1;
    }
    int mid=(S+D)/2;
    if(st<=S&&dr>=D)
    {
        if(AINT[2*nod]==val)return unde(2*nod,st,dr,val,S,mid);
        else if(AINT[2*nod+1]==val)return unde(2*nod+1,st,dr,val,mid+1,D);
        else return -1;
    }
    if(dr<=mid)return unde(2*nod,st,dr,val,S,mid);
    else if(st>mid)return unde(2*nod+1,st,dr,val,mid+1,D);
    int x,y;
    x=unde(2*nod,st,dr,val,S,mid);
    y=unde(2*nod+1,st,dr,val,mid+1,D);
    if(x!=-1)return x;
    return y;
}
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i];A[i]=V[i];u(1,1,N,V[i],i);
    }
    sort(A+1,A+1+N);
    int p=0;
    long long nr=0;
    for(int i=1;i<=N;i++)
    {
        int poz=unde(1,p+1,N,A[i],1,N);
        if(poz==-1)poz=unde(1,1,p-1,A[i],1,N);
        if(p>poz)
        {
            nr+=N-p-(q(N)-q(p));
            p=0;
        }
        nr+=poz-p-(q(poz)-q(p));
        p=poz;
        u(p,1);
        u(1,1,N,1<<30,p);
    }
    cout<<nr;
    return 0;
}
