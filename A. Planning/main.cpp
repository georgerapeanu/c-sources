#include <iostream>
#include <algorithm>
using namespace std;
int N,K;
bool U[600005];
int mex;
int sol[300005];
long long rez;
pair<int,int> V[300005];
bool cmp(pair<int,int> a,pair<int,int> b)
{
    if(a.first!=b.first)return a.first>b.first;
    return a.second<b.second;
}
int main()
{
    cin>>N>>K;
    mex=K+1;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i].first;
        V[i].second=i;
    }
    sort(V+1,V+1+N,cmp);
    for(int i=1;i<=N;i++)
    {
        if(mex>=V[i].second)
        {
            rez+=1LL*V[i].first*(mex-V[i].second);
            U[mex]=1;
            sol[V[i].second]=mex;
        }
        else
        {
            sol[V[i].second]=V[i].second;
            U[V[i].second]=1;
        }
        while(U[mex])mex++;
    }
    cout<<rez<<"\n";
    for(int i=1;i<=N;i++)cout<<sol[i]<<" ";
    return 0;
}
