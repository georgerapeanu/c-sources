#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;
double AINT[400005];
double lazy[400005];///tre facut 1
double lazyoff[400005];
void propag(int nod,int st,int dr)
{
    if(st==dr||(lazy[nod]==1&&lazyoff[nod]==0))return ;
    int mid=(st+dr)/2;
    AINT[nod*2]=(lazy[nod])*AINT[2*nod]+lazyoff[nod]*(mid-st+1);
    lazy[nod*2]*=lazy[nod];lazyoff[2*nod]=lazyoff[nod*2]*lazy[nod]+lazyoff[nod];
    AINT[nod*2+1]=(lazy[nod])*AINT[2*nod+1]+lazyoff[nod]*(dr-mid);
    lazy[nod*2+1]*=lazy[nod];lazyoff[2*nod+1]=lazyoff[nod*2+1]*lazy[nod]+lazyoff[nod];
    lazy[nod]=1;lazyoff[nod]=0;
}
void build(int nod,int st,int dr)
{
    if(st==dr)
    {
        cin>>AINT[nod];
        return ;
    }
    int mid=(st+dr)/2;
    build(nod*2,st,mid);
    build(nod*2+1,mid+1,dr);
    AINT[nod]=AINT[2*nod]+AINT[2*nod+1];
}
void u(int nod,int st,int dr,int S,int D,double val,double off)
{
    propag(nod,st,dr);
    if(S<=st&&dr<=D)
    {
        AINT[nod]=(val)*AINT[nod]+off*(dr-st+1);
        lazy[nod]*=val;lazyoff[nod]=lazyoff[nod]*val+off;
        return ;
    }
    if(dr<S||D<st)
    {
        return ;
    }
    int mid=(st+dr)/2;
    u(nod*2,st,mid,S,D,val,off);
    u(nod*2+1,mid+1,dr,S,D,val,off);
    AINT[nod]=AINT[2*nod]+AINT[2*nod+1];
}
double q(int nod,int st,int dr,int S,int D)
{
    propag(nod,st,dr);
    if(D<st||dr<S)
        return 0;
    if(S<=st&&dr<=D)
        return AINT[nod];
    int mid=(st+dr)/2;
    return q(nod*2,st,mid,S,D)+q(nod*2+1,mid+1,dr,S,D);
}
int N,M;
int main()
{
    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);
    cin>>N>>M;
    for(int i=1;i<=4*N;i++)
        lazy[i]=1;
    build(1,1,N);
    for(int i=1;i<=M;i++)
    {
        int t;
        cin>>t;
        if(t==2)
        {
            int l,r;
            cin>>l>>r;
            cout<<fixed<<setprecision(6)<<q(1,1,N,l,r)<<"\n";
        }
        else
        {
            int l1,l2,r1,r2;
            cin>>l1>>r1>>l2>>r2;
            double a,b;
            a=q(1,1,N,l1,r1);
            b=q(1,1,N,l2,r2);
            u(1,1,N,l1,r1,(r1-l1)/(r1-l1+1),(((double)1)/(r1-l1+1))*(((double)1)/(r2-l2+1))*b);
            u(1,1,N,l2,r2,(r2-l2)/(r2-l2+1),(((double)1)/(r2-l2+1))*(((double)1)/(r1-l1+1))*a);
        }
    }
    return 0;
}
