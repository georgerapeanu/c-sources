#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#define rad 40
using namespace std;
int N,S,A,B,C;
int invA,rez;
const int MOD=1000000007;
int nxt(int val)
{
    return (1LL*val*A+B)%C;
}
int ant(int val)
{
    return ((1LL*(val-B)*invA)%C+1LL*C)%C;
}
int lgpow(int b,int e,int MOD)
{
    int p=1;
    while(e)
    {
        if(e&1)p=(1LL*b*p)%MOD;
        b=(1LL*b*b)%MOD;
        e>>=1;
    }
    return p;
}
struct bucket{
    int fstS,lastS,l,r,maxim,minim;
}V[3000000/rad+5];
pair<int,int> AINT[4*3000000/rad+5];
void u(int nod,int st,int dr,int pos)
{
    if(st==dr)
    {
        AINT[nod]={V[pos].maxim,V[pos].maxim};
        return ;
    }
    int mid=(st+dr)/2;
    if(pos<=mid)u(nod*2,st,mid,pos);
    else        u(nod*2+1,mid+1,dr,pos);
    AINT[nod].first=max(AINT[2*nod].first,AINT[2*nod+1].first);
    AINT[nod].second=min(AINT[2*nod].second,AINT[2*nod+1].second);
}
int qS(int nod,int st,int dr,int pos,int val)
{
    if(st==dr)return (val>=V[st].maxim||st==pos ? st-1:st);
    if((st+dr)/2+1>=pos)return qS(nod*2,st,(st+dr)/2,pos,val);
    if(AINT[nod].first<=val)return st-1;
    if(AINT[nod].second>val)return min(dr+1,pos-1);
    int tmp=qS(nod*2+1,(st+dr)/2+1,dr,pos,val);
    if(tmp==(st+dr)/2)return qS(nod*2,st,(st+dr)/2,pos,val);
    else return tmp;
}
int qD(int nod,int st,int dr,int pos,int val)
{
    if(st==dr)return (val>V[st].maxim||st==pos ? dr+1:st);
    if((st+dr)/2<=pos)return qD(nod*2+1,(st+dr)/2+1,dr,pos,val);
    if(AINT[nod].first<val)return dr+1;
    if(AINT[nod].second>=val)return max(st-1,pos+1);
    int tmp=qD(nod*2,st,(st+dr)/2,pos,val);
    if(tmp==(st+dr)/2+1)return qD(nod*2+1,(st+dr)/2+1,dr,pos,val);
    else return tmp;
}
int main() {
    scanf("%d %d %d %d %d",&N,&S,&A,&B,&C);
    invA=lgpow(A,C-2,C);
    int lval=ant(S);
    int buc=(N-1)/rad+1,ind=1;
    for(int i=1;i<=N;i+=rad,ind++)
    {
        V[ind].l=i;V[ind].r=min(N,i+rad-1);V[ind].maxim=V[ind].lastS=V[ind].fstS=nxt(lval);
        for(int j=i+1;j<=V[ind].r;j++)
        {
            V[ind].lastS=nxt(V[ind].lastS);
            V[ind].maxim=max(V[ind].maxim,V[ind].lastS);
        }
        lval=V[ind].lastS;
        u(1,1,buc,ind);
    }
    V[buc+1].l=N+1;
    int val=S,val1=ant(S),val2=nxt(S);
    for(int i=1;i<=buc;i++)
    {
        for(int j=V[i].l;j<=V[i].r;j++)
        {
            int st=j-1,dr=j+1,tmp1=val1,tmp2=val2;
            while(st>=V[i].l&&tmp1<=val)
            {
                st--;
                tmp1=ant(tmp1);
            }
            if(st<V[i].l)
            {
                bucket tmp=V[qS(1,1,buc,i,val)];
                tmp1=tmp.lastS;st=tmp.r;
                while(st&&tmp1<=val)
                {
                    st--;
                    tmp1=ant(tmp1);
                }
            }
            while(dr<=V[i].r&&tmp2<val)
            {
                dr++;
                tmp2=nxt(tmp2);
            }
            if(dr>V[i].r)
            {
                bucket tmp=V[qD(1,1,buc,i,val)];
                tmp2=tmp.fstS;dr=tmp.l;
                while(dr<=N&&tmp2<val)
                {
                    dr++;
                    tmp2=nxt(tmp2);
                }
            }
            //if(j%10000==0)fprintf(stderr,"%d\n",j);
            rez=(rez+(1LL*((1LL*(j-st)*(dr-j))%MOD)*val)%MOD)%MOD;
            val1=val;val=val2;val2=nxt(val2);
        }
    }
    printf("%d",rez);
    return 0;
}
