#include <iostream>
#include <vector>
using namespace std;
int AINT[800005];
int dp[200005];
void build(int nod,int st,int dr)
{
    if(st==dr)
    {
        AINT[nod]=dp[st];
        return ;
    }
    int mid=(st+dr)/2;
    build(nod*2,st,mid);
    build(nod*2+1,mid+1,dr);
    AINT[nod]=min(AINT[2*nod],AINT[2*nod+1]);
}
void u(int nod,int st,int dr,int pos,int val)
{
    if(dr<pos||st>pos)return ;
    if(st==dr){AINT[nod]=val;return ;}
    int mid=(st+dr)/2;
    u(nod*2,st,mid,pos,val);
    u(nod*2+1,mid+1,dr,pos,val);
    AINT[nod]=min(AINT[2*nod],AINT[2*nod+1]);
}
int q(int nod,int st,int dr,int S,int D)
{
    if(dr<S||st>D)return 1<<30;
    if(S<=st&&dr<=D)return AINT[nod];
    int mid=(st+dr)/2;
    return min(q(nod*2,st,mid,S,D),q(nod*2+1,mid+1,dr,S,D));
}
int N,Q;
vector<int> V[200005];
int B[200005],rez;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
        {cin>>B[i];rez+=!B[i];}
    cin>>Q;
    for(int i=1;i<=Q;i++)
    {
        int x,y;
        cin>>x>>y;
        V[x].push_back(y);
    }
    for(int i=1;i<=N+1;i++)dp[i]=1<<30;
    build(1,0,N+1);
    for(int i=0;i<N;i++)
    {
        vector<int> updates;
        for(auto it:V[i+1])
        {
            dp[it+1]=min(dp[it+1],q(1,0,N+1,i,it+1));
            updates.push_back(it+1);
        }
        dp[i+1]=min(dp[i],dp[i+1])+(B[i+1] ? 1:-1);///indiferent de ce o ales ceilalti,ei nu o luat in seama costul pozitiei i+1,asta facem noi aici
        updates.push_back(i+1);
        dp[i]=1<<30;updates.push_back(i);
        for(auto it:updates)
            u(1,0,N+1,it,dp[it]);
    }
    rez+=min(dp[N+1],dp[N]);
    cout<<rez;
    return 0;
}
