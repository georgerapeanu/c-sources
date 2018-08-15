#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
long long S[100005];
vector<int> G[100005];
int V[100005];
int P;
int N,Q;
long long s;
void dfs(int nod,long long sum)
{
    if(nod)S[++S[0]]=sum;
    for(auto it:G[nod])
    {
        dfs(it,sum+V[it]);
    }
}
long long solve(long long s)
{
    int st=1,dr=S[0]+1;
    while(dr-st>1)
    {
        int mid=(st+dr)/2;
        if(S[mid]>s)dr=mid;
        else st=mid;
    }
    return (S[st]<=s ? S[st]:-1);
}
int main()
{
    cin>>N>>Q;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i]>>P;
        G[P+1].push_back(i);
    }
    dfs(0,0);sort(S+1,S+1+S[0]);S[S[0]+1]=1LL<<62;
    for(int i=1;i<=Q;i++)
    {
        cin>>s;
        long long rez=solve(s);
        if(rez==-1)cout<<"none"<<"\n";
        else cout<<rez<<"\n";
    }
    return 0;
}
