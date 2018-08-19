#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
int N,K,x,y;
vector<int> V[1001];
bitset<1001> viz;
int dfs(int nod)
{
    viz[nod]=1;
    int w=0;
    for(auto it:V[nod])
    {
        if(!viz[it])
        {
            if(!dfs(it)&&(it<w||!w))
            {
                w=it;
            }
        }
    }
    return w;
}
int main()
{
    cin>>N>>K;
    for(int i=1;i<N;i++)
    {
        cin>>x>>y;
        V[x].push_back(y);
        V[y].push_back(x);
    }
    int l=dfs(K);
    if(l)
        cout<<"First player wins flying to airport "<<l;
    else
        cout<<"First player loses";
    return 0;
}

