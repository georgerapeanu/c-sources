#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
int N,M,nrcomp,x,y,apar[1001],dir[1001],rez,K;
vector <int> V[1001];
vector <int> comp[1001];
bitset<1001> viz,cdir,edir;
int S[1001];
void dfs(int nod)
{
    viz[nod]=1;
    apar[nod]=nrcomp;
    cdir[nrcomp]=cdir[nrcomp]|edir[nod];
    comp[nrcomp].push_back(nod);
    S[nrcomp]+=V[nod].size();
    for(auto it:V[nod])
    {
        if(!viz[it])
            dfs(it);
    }
}
int main()
{
    cin>>N>>M>>K;
    for(int i=1;i<=M;i++)
    {
        cin>>x>>y;
        V[x].push_back(y);
        V[y].push_back(x);
    }
    for(int i=1;i<=K;i++)
    {
        cin>>dir[i];
        edir[dir[i]]=1;
    }
    for(int i=1;i<=N;i++)
    {
        if(!viz[i])
        {
            nrcomp++;
            dfs(i);
        }
    }
    for(int i=1;i<=K;i++)
    {
        int noduri=0,muchii=0;
        for(int j=1;j<=nrcomp;j++)
        {
            if(!cdir[j]||j==apar[dir[i]])
            {
                noduri+=comp[j].size();
                muchii+=S[j]/2;
            }
        }
        if(noduri*(noduri-1)/2-muchii>rez)
            rez=noduri*(noduri-1)/2-muchii;
    }
    cout<<rez;
    return 0;
}
