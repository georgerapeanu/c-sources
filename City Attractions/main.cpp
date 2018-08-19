#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
vector<int> G[300005];
int d1[300005];
int s1[300005];
int d2[300005];
int unde[300005];
int r1[300005];
int rs1[300005];
int r2[300005];
int V[300005];
int N;
long long K;
void dfs(int nod,int tata)
{
    d1[nod]=-(1<<28);r1[nod]=1<<30;
    s1[nod]=-(1<<28);rs1[nod]=1<<30;
    for(auto it:G[nod])
    {
        if(it==tata)continue;
        dfs(it,nod);
        if(V[it]-1>d1[nod]||(V[it]-1==d1[nod]&&it<r1[nod]))
        {
            if(unde[nod]!=it)
            {
                s1[nod]=d1[nod];
                rs1[nod]=r1[nod];
            }
            d1[nod]=V[it]-1;
            r1[nod]=it;
            unde[nod]=it;
        }
        if(d1[it]-1>d1[nod]||(d1[it]-1==d1[nod]&&r1[it]<r1[nod]))
        {
            if(unde[nod]!=it)
            {
                s1[nod]=d1[nod];
                rs1[nod]=r1[nod];
            }
            d1[nod]=d1[it]-1;
            r1[nod]=r1[it];
            unde[nod]=it;
        }
        if((V[it]-1>s1[nod]||(V[it]-1==s1[nod]&&it<rs1[nod]))&&unde[nod]!=it)
        {
            s1[nod]=V[it]-1;
            rs1[nod]=it;
        }
        if((d1[it]-1>s1[nod]||(d1[it]-1==s1[nod]&&r1[it]<rs1[nod]))&&unde[nod]!=it)
        {
            s1[nod]=d1[it]-1;
            rs1[nod]=r1[it];
        }
    }
}
void dfs2(int nod,int tata)
{
    d2[nod]=-(1<<28);r2[nod]=1<<30;
    if(V[tata]-1>d2[nod]||(V[tata]-1==d2[nod]&&tata<r2[nod]))
    {
        d2[nod]=V[tata]-1;
        r2[nod]=tata;
    }
    if((d2[tata]-1>d2[nod]||(d2[tata]-1==d2[nod]&&r2[tata]<r2[nod])))
    {
        d2[nod]=d2[tata]-1;
        r2[nod]=r2[tata];
    }
    if((d1[tata]-1>d2[nod]||(d1[tata]-1==d2[nod]&&r1[tata]<r2[nod]))&&unde[tata]!=nod)
    {
        d2[nod]=d1[tata]-1;
        r2[nod]=r1[tata];
    }
    if((s1[tata]-1>d2[nod]||(s1[tata]-1==d2[nod]&&rs1[tata]<r2[nod]))&&rs1[tata]!=nod)
    {
        d2[nod]=s1[tata]-1;
        r2[nod]=rs1[tata];
    }
    for(auto it:G[nod])
    {
       if(it!=tata)dfs2(it,nod);
    }
}
int poz[300005];
vector<int> ceva;
int main() {
    //freopen("in","r",stdin);
    V[0]=-(1<<28);
    cin>>N>>K;
    for(int i=1;i<=N;i++)cin>>V[i];
    for(int i=1;i<N;i++)
    {
        int x,y;
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(1,0);
    dfs2(1,0);
    ceva.push_back(0);
    int nod=1,ind=1;
    while(!poz[nod])
    {
        ceva.push_back(nod);
        poz[nod]=ind++;
        if(d1[nod]>d2[nod]||(r1[nod]<r2[nod]&&d1[nod]==d2[nod]))
            nod=r1[nod];
        else
            nod=r2[nod];
    }
    K++;
    if(K<poz[nod])
    {
        cout<<ceva[K];return 0;
    }
    K=K-poz[nod]+1;
    K=(K-1)%(ind-poz[nod])+1;
    cout<<ceva[poz[nod]-1+K];
    return 0;
}
