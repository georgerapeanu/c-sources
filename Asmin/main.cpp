#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
ifstream f("asmin.in");
ofstream g("asmin.out");
int V[16005];
int R[16005];
int K,N;
vector<int> G[16005];
int mini=1<<30;
int nr=1;
int S;
int rez[16005];
void dfs(int nod,int tata,bool c,int suma)
{
    if(!c)
    {
        V[nod]=((R[nod]-suma)%K+K)%K;
        S+=V[nod];
        for(auto it:G[nod])
        {
            if(it==tata)continue;
            dfs(it,nod,0,R[nod]);
        }
        return ;
    }
    if(mini>suma)
    {
        mini=suma;
        nr=1;
        rez[0]=1;rez[1]=nod;
    }
    else if(mini==suma){nr++;rez[++rez[0]]=nod;}
    for(auto it:G[nod])
    {
        if(it==tata)continue;
        int a,b;
        a=V[nod];b=V[it];
        V[it]=R[it];V[nod]=((R[nod]-R[it])%K+K)%K;
        dfs(it,nod,1,suma+V[nod]+V[it]-a-b);
        V[nod]=a;V[it]=b;
    }
}
int main()
{
    f>>N>>K;
    for(int i=1;i<N;i++)
    {
        int a,b;
        f>>a>>b;G[a].push_back(b);G[b].push_back(a);
    }
    for(int i=1;i<=N;i++)f>>R[i];
    dfs(1,0,0,0);
    dfs(1,0,1,S);
    g<<mini<<" "<<nr<<"\n";sort(rez+1,rez+1+rez[0]);
    for(int i=1;i<=rez[0];i++)g<<rez[i]<<" ";
    f.close();
    g.close();
    return 0;
}
