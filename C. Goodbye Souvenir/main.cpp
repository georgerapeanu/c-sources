#include <cstdio>
#include <set>
#include <cstring>
#include <algorithm>
using namespace std;
struct AINT
{
    long long A[400005];
    long long lazy[400005];
    AINT()
    {
        memset(A,0,sizeof(A));
        memset(lazy,0,sizeof(lazy));
    }
    void propag(int nod,int st,int dr)
    {
        if(!lazy[nod])return ;
        A[nod]+=lazy[nod];
        if(st!=dr)
        {
            lazy[2*nod]+=lazy[nod];
            lazy[2*nod+1]+=lazy[nod];
        }
        lazy[nod]=0;
    }
    void u(int nod,int st,int dr,int L,int R,long long val)
    {
        if(dr<L||R<st)return ;
        propag(nod,st,dr);
        if(L<=st&&dr<=R)
        {
            lazy[nod]+=val;
            return ;
        }
        u(nod*2,st,(st+dr)/2,L,R,val);
        u(nod*2+1,(st+dr)/2+1,dr,L,R,val);
        propag(2*nod,st,(st+dr)/2);propag(2*nod+1,(st+dr)/2+1,dr);
        A[nod]=A[2*nod]+A[2*nod+1];
    }
    long long q(int nod,int st,int dr,int L,int R)
    {
        if(dr<L||R<st)return 0;
        propag(nod,st,dr);
        if(L<=st&&dr<=R)
        {
            return A[nod];
        }
        return q(nod*2,st,(st+dr)/2,L,R)+q(nod*2+1,(st+dr)/2+1,dr,L,R);
    }
}S,D;
int N,M;
int V[100005];
int nxt[100005];
int ant[100005];
int last[100005];
set<int> s[100005];
int main()
{
    scanf("%d %d",&N,&M);
    for(int i=1;i<=N;i++)
    {
        scanf("%d",&V[i]);
        D.u(1,1,N,i,i,D.q(1,1,N,i-1,i-1)-last[V[i]]+i);
        ant[i]=last[V[i]];
        last[V[i]]=i;
        s[V[i]].insert(i);
    }
    memset(last,0,sizeof(last));
    for(int i=N;i;i--)
    {
        S.u(1,1,N,i,i,S.q(1,1,N,i+1,i+1)-last[V[i]]+i);
        nxt[i]=last[V[i]];
        last[V[i]]=i;
    }

    while(M--)
    {
        int t,x,y;
        scanf("%d %d %d",&t,&x,&y);
        if(t==1)
        {
            D.u(1,1,N,x,(nxt[x] ? nxt[x]-1:N),-x+ant[x]);
            S.u(1,1,N,ant[x]+1,x,-x+nxt[x]);
            s[V[x]].erase(x);
            V[x]=y;
            set<int>::iterator it=s[y].lower_bound(x);
            if(it!=s[y].end())nxt[x]=*it;
            else nxt[x]=0;
            if(it!=s[y].begin())
            {
                it--;
                ant[x]=*it;
            }
            else ant[x]=0;
            s[y].insert(x);
            S.u(1,1,N,ant[x]+1,x,x-nxt[x]);
            D.u(1,1,N,x,(nxt[x] ? nxt[x]-1:N),x-ant[x]);
        }
        else
        {
            printf("%lld\n",D.q(1,1,N,y,y)-S.q(1,1,N,x,x));
        }
    }
    return 0;
}
