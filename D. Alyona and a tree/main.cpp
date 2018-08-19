#include <iostream>
#include <vector>
using namespace std;
int N;
vector<pair<int,int> > G[200005];
int ans[200005];
int tmp[200005];
long long S[200005];
long long s[200005];
long long A[200005];
void dfs(int nod,int tata)
{
    int st=0,dr=s[0];
    while(dr-st>1)
    {
        int mid=(st+dr)/2;
        if(S[S[0]]-S[mid]<=A[nod])dr=mid;
        else st=mid;
    }
    if(st)tmp[s[st]]++;
    ans[tata]++;
    for(auto it:G[nod])
    {
        if(tata!=it.first)
        {
            S[0]++;
            S[S[0]]=S[S[0]-1]+it.second;
            s[++s[0]]=it.first;
            dfs(it.first,nod);
            ans[nod]+=ans[it.first];
            s[0]--;
            S[0]--;
        }
    }
    ans[nod]-=tmp[nod];
}
int main()
{
    cin>>N;for(int i=1;i<=N;i++)cin>>A[i];
    for(int i=2;i<=N;i++){int x,y;cin>>x>>y;G[x].push_back({i,y});G[i].push_back({x,y});}
    S[++S[0]]=0;
    s[++s[0]]=1;
    dfs(1,0);
    for(int i=1;i<=N;i++)cout<<ans[i]<<" ";
    return 0;
}
