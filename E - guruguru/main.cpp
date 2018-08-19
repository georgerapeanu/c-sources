#include <iostream>
#define ll long long
using namespace std;
ll N,M;
ll A[100005];
ll a[100005];
ll b[100005];
ll dist(ll x,ll y)
{
    if(x<=y)return y-x;
    return M-x+y;
}
ll cost(ll x)
{
    ll rez=0;
    for(ll i=2;i<=N;i++)
        rez+=min(1+dist(x,A[i]),dist(A[i-1],A[i]));
    return rez;
}
void addprog(ll st,ll dr,ll p,ll q)
{
    b[st]+=p;b[dr+1]-=p;
    a[st]+=q;a[dr+1]-=q;
    b[st]-=st*q;b[dr+1]+=st*q;
}
int main()
{
    cin>>N>>M;
    ll mini=1LL<<60;
    for(ll i=1;i<=N;i++)
        {cin>>A[i];}
    for(ll i=2;i<=N;i++)
    {
        if(A[i-1]<A[i])
        {
            addprog(1,A[i-1],dist(A[i-1],A[i]),0);
            addprog(A[i]+1,M,dist(A[i-1],A[i]),0);
            addprog(A[i-1]+1,A[i],dist(A[i-1],A[i]),-1);
        }
        else
        {
            addprog(A[i]+1,A[i-1],dist(A[i-1],A[i]),0);
            addprog(A[i-1]+1,M,dist(A[i-1],A[i]),-1);
            addprog(1,A[i],A[i],-1);
        }
    }
    for(int i=1;i<=M;i++)
    {
        a[i]+=a[i-1];
        b[i]+=b[i-1];
    }
    for(int i=1;i<=M;i++)
        mini=min(mini,i*a[i]+b[i]);
    cout<<mini;
    return 0;
}
