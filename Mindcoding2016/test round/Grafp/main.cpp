#include <iostream>
#include <vector>
using namespace std;
int K,N,M;
vector<pair<int,int> > E;
int main()
{
    cin>>K>>N>>M;
    if(N>K||M>K){cout<<-1;return 0;}
    if(K!=N&&M!=K){cout<<-1;return 0;}
    if(K==N&&M==K&&K<=3&&K>=2){cout<<-1;return 0;}
    if(K==N&&M==K){cout<<K-1<<"\n";for(int i=1;i<K;i++)cout<<i<<" "<<i+1<<"\n";return 0;}
    if(N==K&&M!=K)
    {
        for(int i=1;i<=K;i+=M)
        {
            for(int j=i;j<i+M&&j<=K;j++)
            {
                for(int k=1;k<i;k++)E.push_back({k,j});
            }
        }
        cout<<E.size()<<"\n";
        for(auto it:E)cout<<it.first<<" "<<it.second<<"\n";
        return 0;
    }
    for(int i=1;i<=K;i+=N)
    {
        for(int j=i;j<i+N&&j<=K;j++)
            for(int k=j+1;k<i+N&&k<=K;k++)
                E.push_back({j,k});
    }
    cout<<E.size()<<"\n";
    for(auto it:E)cout<<it.first<<" "<<it.second<<"\n";
    return 0;
}
