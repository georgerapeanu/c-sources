#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int N,M;
int A[100005];
int B[100005];
int tmp[100005];
pair<int,int> AINT[400005];
int lazy[400005];
void propag(int nod,int st,int dr)
{
    if(nod>4*N||!lazy[nod])return ;
    AINT[nod].first-=lazy[nod];
    AINT[nod].second-=lazy[nod];
    if(st!=dr)
    {
        lazy[2*nod]+=lazy[nod];
        lazy[2*nod+1]+=lazy[nod];
    }
    lazy[nod]=0;
}
void build(int nod,int st,int dr)
{
    if(st==dr)
    {
        AINT[nod].first=AINT[nod].second=A[st];
        return ;
    }
    build(nod*2,st,(st+dr)/2);
    build(nod*2+1,(st+dr)/2+1,dr);
    AINT[nod].first=min(AINT[2*nod].first,AINT[2*nod+1].first);
    AINT[nod].second=max(AINT[2*nod].second,AINT[2*nod+1].second);
}
void u(int nod,int st,int dr,int S,int D)
{
    if(S<=st&&dr<=D){lazy[nod]++;return ;}
    if(dr<S||st>D)return;
    propag(nod,st,dr);
    u(nod*2,st,(st+dr)/2,S,D);
    u(nod*2+1,(st+dr)/2+1,dr,S,D);
    propag(nod*2,st,(st+dr)/2);
    propag(nod*2+1,(st+dr)/2+1,dr);
    AINT[nod].first=min(AINT[2*nod].first,AINT[2*nod+1].first);
    AINT[nod].second=max(AINT[2*nod].second,AINT[2*nod+1].second);
}
int elem(int nod,int st,int dr,int poz)
{
    if(poz>dr||poz<st)return 0;
    propag(nod,st,dr);
    if(st==dr)return AINT[nod].first;
    if(poz<=(st+dr)/2)return elem(nod*2,st,(st+dr)/2,poz);
    else              return elem(nod*2+1,(st+dr)/2+1,dr,poz);
}
int fip(int nod,int st,int dr,int val)
{
    if(st==dr)return st;
    propag(nod,st,dr);
    propag(nod*2,st,(st+dr)/2);
    propag(nod*2+1,(st+dr)/2+1,dr);
    if(AINT[2*nod].first<=val&&val<=AINT[2*nod].second)return fip(nod*2,st,(st+dr)/2,val);
    else                                                 return fip(nod*2+1,(st+dr)/2+1,dr,val);
}
int fiu(int nod,int st,int dr,int val)
{
    if(st==dr)return st;
    propag(nod,st,dr);
    propag(nod*2,st,(st+dr)/2);
    propag(nod*2+1,(st+dr)/2+1,dr);
    if(AINT[2*nod+1].first<=val&&val<=AINT[2*nod+1].second)return fiu(nod*2+1,(st+dr)/2+1,dr,val);
    else                                                   return fiu(nod*2,st,(st+dr)/2,val);
}
int main() {
    cin>>N>>M;
    for(int i=1;i<=N;i++)cin>>A[i];sort(A+1,A+1+N);reverse(A+1,A+1+N);
    for(int i=1;i<=M;i++)cin>>B[i];
    build(1,1,N);
    for(int i=1;i<=M;i++)
    {
        int tmp=elem(1,1,N,B[i]);
        if(!tmp){cout<<i-1;return 0;}
        int st,dr;
        st=fip(1,1,N,tmp);
        dr=fiu(1,1,N,tmp);
        if(st!=1)u(1,1,N,1,st-1);
        u(1,1,N,dr-max(0,B[i]-(st-1))+1,dr);
    }
    cout<<M;
    return 0;
}
