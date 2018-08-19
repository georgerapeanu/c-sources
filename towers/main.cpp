#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>
#include <bitset>
#include <stack>
#define val first
#define pos second
#define best second
using namespace std;
FILE *f=fopen("towers.in","r");
FILE *g=fopen("towers.out","w");
int N,K;
int P[1000005];
int rez[1000005];
vector<int> G[1000005];
int lastnode,node;
bitset<1000005> U;
struct data{
    int first,second;
};
bool cmp(data a,data b)
{
    if(a.first!=b.first)return a.first<b.first;
    return a.second<b.second;
}
data T[1000005];
data Q[1000005];
stack<int> S;
stack<int> ind;
void dfs(int nod)
{
    S.push(nod);
    ind.push(0);
    while(1)
    {
        if(ind.top()<G[S.top()].size())
        {
            S.push(G[S.top()][ind.top()]);
            ind.push(0);
            T[S.top()].best=1;
        }
        else
        {
            int nod=S.top();
            S.pop();
            ind.pop();
            if(S.empty())break;
            T[S.top()].best=max(T[nod].best+1,T[S.top()].best);
            ind.top()++;
        }
    }
}
int main()
{
    fscanf(f,"%d %d",&N,&K);
    T[0].val=1<<30;
    assert(N<=1000000&&K<=1000000);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&T[i].val);
        assert(T[i].val<=1000000000);
        node=i;
        assert(0<=lastnode&&lastnode<=N);
        assert(0<=node&&node<=N);
        while(T[node].val>T[lastnode].val)lastnode=P[lastnode];
        P[node]=lastnode;
        G[lastnode].push_back(node);
        assert(node!=lastnode);
        lastnode=node;
    }
    for(int i=1;i<=K;i++){fscanf(f,"%d",&Q[i].val);Q[i].pos=i;assert(Q[i].val<=1000000000);}
    dfs(0);
    T[0].best=0;
    sort(T+1,T+1+N,cmp);
    for(int i=1;i<=N;i++)
    {
        T[i].best=max(T[i-1].best,T[i].best);
    }
    sort(Q+1,Q+1+K,cmp);
    int wh=0;
    for(int i=1;i<=K;i++)
    {
        while(wh<N&&T[wh+1].val<Q[i].val)wh++;
        rez[Q[i].pos]=T[wh].best;
    }
    for(int i=1;i<=K;i++)fprintf(g,"%d ",rez[i]);
    fclose(f);
    fclose(g);
    return 0;
}
