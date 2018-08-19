#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int N,M;
vector<int> G[100005];
vector<int> cuv[100005];
vector<int> sortaret;
int gr[100005];
bool bagat[100005];
int nr;
int cmp(int a,int b)
{
    if(bagat[a]!=bagat[b])
    {
        if(bagat[a])return -1;
        if(bagat[b])return 1;
    }
    if(a!=b)return (a<b ? -1:1);
    return 0;
}
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N>>M;
    for(int i=1;i<=N;i++)
    {
        int l;
        cin>>l;
        for(int j=1;j<=l;j++)
        {
            int nr;
            cin>>nr;
            cuv[i].push_back(nr);
        }
        if(i!=1)
        {
            int pre=0;
            while(pre<cuv[i-1].size()&&pre<cuv[i].size()&&cuv[i-1][pre]==cuv[i][pre])pre++;
            if(pre==cuv[i-1].size())continue;
            if(pre==cuv[i].size()){cout<<"No";return 0;}
            G[cuv[i-1][pre]].push_back(cuv[i][pre]);
            gr[cuv[i][pre]]++;
        }
    }
    queue<int> Q;
    for(int i=1;i<=M;i++)if(!gr[i])Q.push(i);
    while(!Q.empty())
    {
        int nod=Q.front();Q.pop();
        sortaret.push_back(nod);
        for(auto it:G[nod])
        {
            gr[it]--;
            if(!gr[it])Q.push(it);
        }
    }
    if(sortaret.size()!=M)
    {
        cout<<"No";
        return 0;
    }
    reverse(sortaret.begin(),sortaret.end());
    for(auto it:sortaret)
    {
        int mini=0;
        for(auto it2:G[it])
        {
            if(mini==0||cmp(it2,mini)==-1)
            {
                mini=it2;
            }
        }
        if(bagat[mini]&&it>mini)
        {
            cout<<"No";
            return 0;
        }
        if(!mini)continue;
        if(bagat[mini]&&it<=mini)
        {
            bagat[it]=1;
        }
        else if(it>mini)
        {
            bagat[it]=1;
        }
    }
    cout<<"Yes\n";
    vector<int> ans;
    for(int i=1;i<=M;i++)if(bagat[i])ans.push_back(i);
    cout<<ans.size()<<"\n";
    for(auto it:ans)cout<<it<<" ";
    return 0;
}
