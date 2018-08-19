#include <iostream>
#include <vector>
using namespace std;
int st[200005];
int dr[200005];
int V[200005];
int cat[200005];
int ind;
vector<int> G[200005];
int N;
void dfs(int nod)
{
    V[++ind]=nod;
    st[nod]=ind;
    for(auto it:G[nod])dfs(it);
    dr[nod]=ind;
}
struct node
{
    bool lazy;
    int sum;
}AINT[800005];
void propag(int nod,int st,int dr)
{
    if(!AINT[nod].lazy||st==dr)return ;
    AINT[2*nod].lazy^=1;AINT[2*nod].sum=((dr+st)/2-st+1)-AINT[2*nod].sum;
    AINT[2*nod+1].lazy^=1;AINT[2*nod+1].sum=(dr-(st+dr)/2)-AINT[2*nod+1].sum;
    AINT[nod].lazy=0;
}
void u(int nod,int st,int dr,int S,int D)
{
    propag(nod,st,dr);
    if(dr<S||D<st)return ;
    if(S<=st&&dr<=D)
    {
        AINT[nod].sum=(dr-st+1)-AINT[nod].sum;
        AINT[nod].lazy^=1;
        return ;
    }
    u(nod*2,st,(st+dr)/2,S,D);
    u(nod*2+1,(st+dr)/2+1,dr,S,D);
    AINT[nod].sum=AINT[2*nod].sum+AINT[2*nod+1].sum;
}
int q(int nod,int st,int dr,int S,int D)
{
    propag(nod,st,dr);
    if(dr<S||D<st)return 0;
    if(S<=st&&dr<=D)return AINT[nod].sum;
    return q(nod*2,st,(st+dr)/2,S,D)+q(nod*2+1,(st+dr)/2+1,dr,S,D);
}
void build(int nod,int st,int dr)
{
    if(st==dr)
    {
        AINT[nod].sum=cat[V[st]];
        return ;
    }
    build(nod*2,st,(st+dr)/2);
    build(nod*2+1,(st+dr)/2+1,dr);
    AINT[nod].sum=AINT[nod*2].sum+AINT[nod*2+1].sum;
}
int main()
{
    cin>>N;
    for(int i=2;i<=N;i++)
    {
        int p;
        cin>>p;
        G[p].push_back(i);
    }
    dfs(1);
    for(int i=1;i<=N;i++)cin>>cat[i];
    build(1,1,N);
    int Q;
    cin>>Q;
    while(Q--)
    {
        string a;
        int val;
        cin>>a>>val;
        if(a=="get")
        {
            cout<<q(1,1,N,st[val],dr[val])<<"\n";
        }
        else
        {
            u(1,1,N,st[val],dr[val]);
        }
    }
    return 0;
}
