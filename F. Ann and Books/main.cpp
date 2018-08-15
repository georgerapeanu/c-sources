#include <iostream>
#include <map>
#include <algorithm>
#define rad 340
using namespace std;
int N,K;
long long V[100005];
long long L[100005];
long long R[100005],rez;
long long Rez[100005];
int frL[300005];
int frR[300005];
map<long long,int> M;
int l,r;
struct query
{
    int l,r,ind;
    bool operator < (const query &other)
    {
        if(l/rad!=other.l/rad)return l<other.l;
        return r<other.r;
    }
}q[100005];
void insl(int &l)
{
    l--;
    frL[V[l-1]]++;
    frR[V[l]]++;
    rez+=frR[R[l-1]];
}
void insr(int &r)
{
    r++;
    frR[V[r]]++;
    frL[V[r-1]]++;
    rez+=frL[L[r]];
}
void dell(int &l)
{
    rez-=frR[R[l-1]];
    frL[V[l-1]]--;
    frR[V[l]]--;
    l++;
}
void delr(int &r)
{
    rez-=frL[L[r]];
    frR[V[r]]--;
    frL[V[r-1]]--;
    r--;
}
int main()
{
    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);
    cin>>N>>K;
    for(int i=1;i<=N;i++)cin>>V[i];
    for (int i=1;i<=N;i++)
    {
        int val;
        cin>>val;
        V[i]=val*(V[i]==1 ? 1:-1)+V[i-1];
        M[V[i]]=1;
        M[V[i]+K]=1;
        M[V[i]-K]=1;
    }
    M[0]=M[K]=M[-K]=1;
    int ind=0;
    for(auto &it:M)it.second=++ind;
    for(int i=0;i<=N;i++)
    {
        L[i]=M[V[i]-K];
        R[i]=M[V[i]+K];
        V[i]=M[V[i]];
    }
    int Q;
    cin>>Q;
    for(int i=1;i<=Q;i++)
    {
        cin>>q[i].l>>q[i].r;
        q[i].ind=i;
    }
    sort(q+1,q+1+Q);
    int l=1,r=0;
    for(int i=1;i<=Q;i++)
    {
        while(r<q[i].r)
        {
            insr(r);
        }
        while(r>q[i].r)
        {
            delr(r);
        }
        while(l<q[i].l)
        {
            dell(l);
        }
        while(l>q[i].l)
        {
            insl(l);
        }
        Rez[q[i].ind]=rez;
    }
    for(int i=1;i<=Q;i++)cout<<Rez[i]<<"\n";
    return 0;
}
