#include <iostream>
#include <vector>
using namespace std;
vector<int> G[500005];
long long rez,tmp;
int N,ceva;
int W[500005],nrspecial;
bool special[500005];
int lvl[500005];
int nr[500005][2];///nr[nod][c]-numarul de drumuri care pleaca din nod pe o muchie de tip c si se incheie in ceva bad
long long L[500005][2];///suma lungimiilor chestilor astora
bool all1=1;
int u=1,v;
vector<int> path;
void dfs(int nod,int tata)
{
    lvl[nod]=1+lvl[tata];
    int numbad=0;
    W[nod]=1;
    nr[nod][0]=nr[nod][1]=L[nod][0]=L[nod][1]=0;
    for(auto it:G[nod])
    {
        if(it==tata)continue;
        dfs(it,nod);
        W[nod]+=W[it];
        numbad+=(W[it]&1);
        if(W[it]&1)
        {
            nr[nod][1]+=nr[it][0]+1;
            L[nod][1]+=L[it][0]+nr[it][0]+1;
        }
        else
        {
            nr[nod][0]+=nr[it][1];
            L[nod][0]+=L[it][1]+nr[it][1];
        }
    }
    numbad+=(W[nod]&1);
    all1&=(numbad==1);
    ceva=max(ceva,numbad);
    if(numbad==3){special[nod]=1;nrspecial++;}
}
void computedp(int nod,int tata)
{
    tmp+=(L[nod][1]-nr[nod][1])/2+nr[nod][1];
    for(auto it:G[nod])
    {
        if(it==tata)continue;
        if(W[it]&1)
        {
            nr[nod][1]-=(nr[it][0]+1);
            L[nod][1]-=(L[it][0]+nr[it][0]+1);
            nr[it][1]+=nr[nod][0]+1;
            L[it][1]+=L[nod][0]+nr[nod][0]+1;
            computedp(it,nod);
            nr[it][1]-=(nr[nod][0]+1);
            L[it][1]-=(L[nod][0]+nr[nod][0]+1);
            nr[nod][1]+=nr[it][0]+1;
            L[nod][1]+=L[it][0]+nr[it][0]+1;
        }
        else
        {
            nr[nod][0]-=(nr[it][1]);
            L[nod][0]-=(L[it][1]+nr[it][1]);
            nr[it][0]+=nr[nod][1];
            L[it][0]+=L[nod][1]+nr[nod][1];
            computedp(it,nod);
            nr[it][0]-=nr[nod][1];
            L[it][0]-=(L[nod][1]+nr[nod][1]);
            nr[nod][0]+=nr[it][1];
            L[nod][0]+=L[it][1]+nr[it][1];
        }
    }
}
void dfs2(int nod,int tata,int nrgoten)
{
    if(!v)
    {
        path.push_back(nod);
    }
    nrgoten+=special[nod];
    if(nrgoten==nrspecial&&!v)
    {
        v=nod;
    }
    for(auto it:G[nod])
        if(it!=tata)
        {
            if(special[nod])
            {
                if(W[it]%2==1)dfs2(it,nod,nrgoten);
            }
            else
            {
                if(W[it]%2!=W[nod]%2)dfs2(it,nod,nrgoten);
            }
        }
    if(!v)
    {
        path.pop_back();
    }
}
long long nrofbad(int nod)
{
    return (L[nod][0]-nr[nod][0])/2+nr[nod][0];
}
int main()
{
    cin>>N;
    if(N&1){cout<<0;return 0;}
    for(int i=1;i<N;i++)
    {
        int x,y;
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(1,0);
    if(all1)
    {
        for(int i=2;i<=N;i++)
            if(W[i]%2==0)
                rez+=1LL*(N-W[i])*(W[i]);
        computedp(1,0);
        cout<<rez+tmp/2;
    }
    else
    {
        if(ceva>3)
        {
            cout<<0;
            return 0;
        }
        for(int i=1;i<=N;i++)
            if(special[i]&&lvl[i]>lvl[u])
                u=i;
       if(nrspecial>1)
       {
            dfs(u,0);///recalc weights
            dfs2(u,0,0);
            if(!v)
            {
                cout<<0;
                return 0;
            }
            int nrbadonpath=0;
            for(int i=1;i<path.size();i++)
                if(W[path[i]]&1)
                    nrbadonpath++;
            dfs(u,path[1]);
            dfs(v,path[path.size()-2]);
            rez+=1LL*nrbadonpath*nr[u][1]*nr[v][1]+nrofbad(u)*nr[v][1]+nrofbad(v)*nr[u][1];
       }
       else
       {
           dfs(u,0);
           vector<int> tmp;
           for(auto it:G[u])
            if(W[it]%2==1)
                tmp.push_back(it);
           for(auto it:tmp)
           {
               L[it][0]+=1+nr[it][0];
               nr[it][0]++;
           }
           for(int i=0;i<tmp.size();i++)
                for(int j=i+1;j<tmp.size();j++)
                    rez+=nrofbad(tmp[i])*nr[tmp[j]][0]+nrofbad(tmp[j])*nr[tmp[i]][0];
           cout<<rez;
       }
    }
    return 0;
}
/*
10
1 2
2 3
3 4
1 5
5 6
6 7
1 8
7 9
7 10
26
dfs2 belit
*/
