#include <cstdio>
#include <algorithm>
using namespace std;
int AINT[150005];
int N;
int M;
pair<int,int> P[30005];
pair<pair<int,int>,pair<int,int> > Q[200005];
int rez[200005];
void build(int nod,int st,int dr)
{
    if(st==dr)
    {
        AINT[nod]=1;
        return ;
    }
    int mid=(st+dr)/2;
    build(nod*2,st,mid);
    build(nod*2+1,mid+1,dr);
    AINT[nod]=AINT[2*nod]+AINT[2*nod+1];
}
void u(int nod,int st,int dr,int poz,int val)
{
    if(st==dr)
    {
        AINT[nod]=val;
        return ;
    }
    int mid=(st+dr)/2;
    if(poz<=mid)u(nod*2,st,mid,poz,val);
    else        u(nod*2+1,mid+1,dr,poz,val);
    AINT[nod]=AINT[2*nod]+AINT[2*nod+1];
}
int q(int nod,int st,int dr,int S,int D)
{
    if(dr<S||st>D)return 0;
    if(S<=st&&dr<=D)return AINT[nod];
    int mid=(st+dr)/2;
    return q(nod*2,st,mid,S,D)+q(nod*2+1,mid+1,dr,S,D);
}
int main()
{
    scanf("%d",&N);
    build(1,1,N);
    for(int i=1;i<=N;i++){scanf("%d",&P[i].first);P[i].second=i;}sort(P+1,P+1+N);
    scanf("%d",&M);
    for(int i=1;i<=M;i++){scanf("%d %d %d",&Q[i].second.first,&Q[i].second.second,&Q[i].first.first);Q[i].first.second=i;}sort(Q+1,Q+1+M);
    int ind=1;
    for(int i=1;i<=M;i++)
    {
        while(ind<=N&&P[ind].first<=Q[i].first.first){u(1,1,N,P[ind].second,0);ind++;}
        rez[Q[i].first.second]=q(1,1,N,Q[i].second.first,Q[i].second.second);
    }
    for(int i=1;i<=M;i++)printf("%d\n",rez[i]);
    return 0;
}
