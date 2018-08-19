#include <iostream>
#include <vector>
using namespace std;
long long a[55];
int N,M;
int timp=0;
vector<int> G[55];
void dfs(int nod)
{
    for(auto it:G[nod])
    {
        dfs(it);
        a[nod]+=2*a[it];
    }
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>a[i];
        timp+=a[i];
    }
    for(int i=1;i<=N;i++)
    {
        cin>>M;
        for(int j=1;j<=M;j++)
        {
            int a;
            cin>>a;
            G[i].push_back(a);
        }
    }
    cout<<timp<<" ";
    timp=0;
    dfs(1);
    cout<<a[1];
    return 0;
}
