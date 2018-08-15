#include <iostream>
#include <vector>
using namespace std;
int nrnoduri[100005];
vector<int> G[100005];
int val[100005];
int rad;
int N;
void dfs(int nod)
{
    if(nod==-1)return ;
    nrnoduri[nod]=1;
    for(auto it:G[nod])
    {
        dfs(it);
        if(it!=-1)nrnoduri[nod]+=nrnoduri[it];
    }
}
int rez(int nod,int tata,bool st,int maxst,int mindr)
{
    bool ok=0;
    if(nod==-1)return 0;
    if(!(maxst<=val[nod]&&val[nod]<=mindr))ok=1;
    return rez(G[nod][0],nod,1,maxst,min(mindr,val[nod]))+rez(G[nod][1],nod,0,max(maxst,val[nod]),mindr)+ok;
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        rad^=i;
        cin>>val[i];
        for(int j=0;j<2;j++)
        {
            int tmp;
            cin>>tmp;
            G[i].push_back(tmp);
            if(tmp!=-1)rad^=tmp;
        }
    }
    dfs(rad);
    cout<<rez(rad,0,0,0,(1<<30));
    return 0;
}
