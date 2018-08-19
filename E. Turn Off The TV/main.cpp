#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
int AINT[3200005];
int N;
pair<int,int> V[200005];
map<int,int> M;
int tmp[800006];
void u(int nod,int st,int dr,int poz,int val)
{
    if(dr<poz||st>poz)return ;
    if(st==dr)
    {
        AINT[nod]=val;
        return ;
    }
    u(nod*2,st,(st+dr)/2,poz,val);
    u(nod*2+1,(st+dr)/2+1,dr,poz,val);
    AINT[nod]=min(AINT[2*nod],AINT[2*nod+1]);
}
int q(int nod,int st,int dr,int S,int D)
{
    if(D<st||dr<S)return 1<<30;
    if(S<=st&&dr<=D)return AINT[nod];
    return min(q(nod*2,st,(st+dr)/2,S,D),q(nod*2+1,(st+dr)/2+1,dr,S,D));
}
int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;i++){scanf("%d%d",&V[i].first,&V[i].second);;M[V[i].first]=1;M[V[i].second]=1;M[V[i].second+1]=1;}
    int len=0;
    for(auto &it:M)it.second=++len;
    for(int i=1;i<=N;i++)
    {
        tmp[M[V[i].first]]++;
        tmp[M[V[i].second+1]]--;
    }
    for(int i=1;i<=len;i++){tmp[i]+=tmp[i-1];u(1,1,len,i,tmp[i]);}
    for(int i=1;i<=N;i++)
    {
        if(q(1,1,len,M[V[i].first],M[V[i].second])>1){printf("%d",i);return 0;}
    }
    printf("-1");
    return 0;
}
