#include <iostream>
#include <bitset>
#include <algorithm>
#define NMAX 200005
using namespace std;
pair<int,int> V[NMAX];
int N,K,rez;
bitset <NMAX> U;
bool cmp(pair<int,int> a,pair<int,int> b)
{
    return a.first-a.second<b.first-b.second;
}
int main()
{
    cin>>N>>K;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i].first;
    }
    for(int i=1;i<=N;i++)
    {
        cin>>V[i].second;
    }
    sort(V+1,V+1+N,cmp);
    for(int i=1;i<=N;i++)
    {
        if(V[i].first<=V[i].second)
        {
            K--;
            rez+=V[i].first;
            U[i]=1;
        }
    }
    for(int i=1;i<=N&&K>0;i++)
    {
        if(U[i]) continue;
        K--;
        rez+=V[i].first;
        U[i]=1;
    }
    for(int i=1;i<=N;i++)
    {
        if(!U[i])
            rez+=V[i].second;
    }
    cout<<rez;
    return 0;
}
