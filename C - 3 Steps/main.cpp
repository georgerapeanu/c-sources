#include <iostream>
#include <vector>
using namespace std;
vector<int> G[100005];
long long N,M;
int viz[100005];
bool baga;
long long nr[2];
void dfs(int nod,int tata,int nvl)
{
    viz[nod]=nvl;
    nr[nvl%2]++;
    for(auto it:G[nod])
    {
        if(it!=tata)
        {
            if(!viz[it])dfs(it,nod,nvl+1);
            else if(viz[nod]%2==viz[it]%2)baga=1;
        }
    }
}
int main()
{
    cin>>N>>M;
    for(long long i=1;i<=M;i++)
    {
        long long a,b;
        cin>>a>>b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    dfs(1,0,1);
    if(baga)cout<<N*(N-1)/2-M;
    else cout<<nr[0]*nr[1]-M;
    return 0;
}
