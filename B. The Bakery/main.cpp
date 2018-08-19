#include <iostream>
#include <cstring>
#define NMAX 35000
using namespace std;
int AINT[4*NMAX+5];
int lazy[4*NMAX+5];
int lst[NMAX+5];
int N,K;
int dp[55][NMAX+5];
int V[NMAX+5];
void build(int k,int nod,int st,int dr)
{
    if(st==dr){AINT[nod]=dp[k][st];return ;}
    int mid=(st+dr)/2;
    build(k,2*nod,st,mid);
    build(k,2*nod+1,1+mid,dr);
    AINT[nod]=max(AINT[nod*2],AINT[nod*2+1]);
}
void propag(int nod,int st,int dr)
{
    AINT[nod]+=lazy[nod];
    if(st==dr){lazy[nod]=0;return;}
    lazy[2*nod]+=lazy[nod];
    lazy[2*nod+1]+=lazy[nod];
    lazy[nod]=0;
}
void u(int nod,int st,int dr,int S,int D)
{
    propag(nod,st,dr);
    if(dr<S||st>D)return ;
    if(S<=st&&dr<=D)
    {
        lazy[nod]++;
        propag(nod,st,dr);
        return ;
    }
    int mid=(st+dr)/2;
    u(nod*2,st,mid,S,D);
    u(nod*2+1,mid+1,dr,S,D);
    AINT[nod]=max(AINT[nod*2],AINT[nod*2+1]);
}
int q(int nod,int st,int dr,int S,int D)
{
    propag(nod,st,dr);
    if(dr<S||st>D)return 0;
    if(S<=st&&dr<=D)
    {
        return AINT[nod];
    }
    int mid=(st+dr)/2;
    return max(q(nod*2,st,mid,S,D),q(nod*2+1,mid+1,dr,S,D));
}
int main()
{
    cin>>N>>K;
    for(int i=1;i<=N;i++){cin>>V[i];}
    for(int i=1;i<=N;i++)
    {
        if(!lst[V[i]])dp[1][i]++;
        dp[1][i]+=dp[1][i-1];
        lst[V[i]]=i;
    }
    for(int i=2;i<=K;i++)
    {
        build(i-1,1,1,N);
        memset(lst,0,sizeof(lst));
        memset(lazy,0,sizeof(lazy));
        for(int j=1;j<=N;j++)
        {
            u(1,1,N,lst[V[j]],j-1);
            lst[V[j]]=j;
            if(j<=i)dp[i][j]=j;
            else
            {
                dp[i][j]=q(1,1,N,1,j);
            }
        }
    }
    cout<<dp[K][N];
    return 0;
}
