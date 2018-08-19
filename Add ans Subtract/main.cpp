#include <iostream>

using namespace std;
struct inter
{
    int st,dr;
    long long val;
    bool operator <(const inter other) const
    {
        return val<other.val;
    }
    bool operator >(const inter other) const
    {
        return val>other.val;
    }
    inter operator +(inter other)
    {
        inter rez;
        rez.val=val+other.val;
        rez.st=st;
        rez.dr=other.dr;
        return rez;
    }
};
struct nod
{
    inter whole_min,whole_max;
    inter full;
    inter l_min,l_max;
    inter r_min,r_max;
    bool activ;
    bool lazy;
    void rev()
    {
        swap(l_min,l_max);
        swap(r_min,r_max);
        swap(whole_min,whole_max);
        full.val*=-1;
        l_min.val*=-1;
        l_max.val*=-1;
        r_min.val*=-1;
        r_max.val*=-1;
        whole_max.val*=-1;
        whole_min.val*=-1;
    }
};
int N;
int V[100000+5];
long long rez[100005];
nod AINT[4*100000+5];
nod combina(nod a,nod b)
{
    nod ans;
    if(!a.activ&&!b.activ)
    {
        ans.activ=0;
        return ans;
    }
    if(!a.activ){ans=b;ans.lazy=0;return ans;}
    if(!b.activ){ans=a;ans.lazy=0;return ans;}
    ans.full=a.full+b.full;
    ans.whole_min=min(min(a.whole_min,b.whole_min),a.r_min+b.l_min);
    ans.whole_max=max(max(a.whole_max,b.whole_max),a.r_max+b.l_max);
    ans.l_min=min(a.l_min,a.full+b.l_min);
    ans.l_max=max(a.l_max,a.full+b.l_max);
    ans.r_min=min(b.r_min,a.r_min+b.full);
    ans.r_max=max(b.r_max,a.r_max+b.full);
    ans.lazy=0;
    ans.activ=1;
    return ans;
}
void propag(int nod,int st,int dr)
{
    if(!AINT[nod].lazy||st==dr)return ;
    AINT[2*nod].lazy^=1;
    AINT[2*nod+1].lazy^=1;
    AINT[nod].lazy=0;
    AINT[2*nod].rev();
    AINT[2*nod+1].rev();
}
void build(int nod,int st,int dr)
{
    if(st==dr)
    {
           AINT[nod].whole_max={st,dr,-(1LL<<61)};
           AINT[nod].whole_min={st,dr,1LL<<61};
           AINT[nod].l_min=AINT[nod].l_max={st,dr,V[st]};
           AINT[nod].r_min=AINT[nod].r_max={st,dr,V[st]};
           AINT[nod].full={st,dr,2LL*V[st]};
           AINT[nod].lazy=0;
           AINT[nod].activ=1;
           return ;
    }
    int mid=(st+dr)/2;
    build(nod*2,st,mid);
    build(nod*2+1,mid+1,dr);
    AINT[nod]=combina(AINT[2*nod],AINT[2*nod+1]);
}
void u(int nod,int st,int dr,int poz)
{
    propag(nod,st,dr);
    if(st==dr)
    {
       AINT[nod].activ=0;
       return ;
    }
    int mid=(st+dr)/2;
    if(poz<=mid)u(nod*2,st,mid,poz);
    else        u(nod*2+1,mid+1,dr,poz);
    AINT[nod]=combina(AINT[2*nod],AINT[2*nod+1]);
}
void lazy_u(int nod,int st,int dr,int S,int D)
{
    propag(nod,st,dr);
    if(dr<S||st>D)return ;
    if(S<=st&&dr<=D)
    {
        AINT[nod].lazy^=1;
        AINT[nod].rev();
        return ;
    }
    int mid=(st+dr)/2;
    lazy_u(nod*2,st,mid,S,D);
    lazy_u(nod*2+1,mid+1,dr,S,D);
    AINT[nod]=combina(AINT[2*nod],AINT[2*nod+1]);
}
int main() {
    cin>>N;
    for(int i=1;i<=N;i++){cin>>V[i];if(i%2==0)V[i]*=-1;}
    build(1,1,N);
    for(int i=N;i>0;i-=2)
    {
        rez[i]=AINT[1].full.val/2;
        int st=AINT[1].whole_min.st,dr=AINT[1].whole_min.dr;
        u(1,1,N,st);
        u(1,1,N,dr);
        lazy_u(1,1,N,st,dr);
    }
    build(1,1,N);
    long long mini=1LL<<61,sum=0;
    int poz=0;
    for(int i=N;i;i--)
    {
        sum+=V[i];
        if(mini>sum)
        {
            mini=sum;
            poz=i;
        }
        sum+=V[i];
    }
    u(1,1,N,poz);
    if(poz!=N)lazy_u(1,1,N,poz+1,N);
    for(int i=N-1;i>0;i-=2)
    {
        rez[i]=AINT[1].full.val/2;
        int st=AINT[1].whole_min.st,dr=AINT[1].whole_min.dr;
        u(1,1,N,st);
        u(1,1,N,dr);
        lazy_u(1,1,N,st,dr);
    }
    for(int i=1;i<=N;i++)cout<<rez[i]<<" ";
    return 0;
}
