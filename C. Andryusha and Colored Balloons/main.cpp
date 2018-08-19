#include <iostream>
#include <vector>
using namespace std;
vector<int> G[200005];
int N;
int x,y;
int nrcul;
int cul[200005];
void dfs(int nod,int tata,int ftata,int C)
{
    cul[nod]=C;
    int nC=1;
    for(auto it:G[nod])
    {
        if(it!=tata)
        {
            while(nC==cul[tata]||nC==cul[nod])
                nC=nC%nrcul+1;
            dfs(it,nod,tata,nC);
            nC=nC%nrcul+1;
        }
    }
}
int main()
{
    cin>>N;
    for(int i=1;i<N;i++)
    {
        cin>>x;
        cin>>y;
        G[x].push_back(y);
        G[y].push_back(x);
        nrcul=max(nrcul,(int)max(G[x].size(),G[y].size()));
    }
    nrcul++;
    dfs(1,0,0,1);
    cout<<nrcul<<"\n";
    for(int i=1;i<=N;i++)
        cout<<cul[i]<<" ";
    return 0;
}
