#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<pair<pair<int,int>,int> > V[200005];
int H,W;
int N;
pair<int,int> rez[100005];
bool cmp1(pair<pair<int,int>,int> a,pair<pair<int,int>,int> b)
{
    if(a.first.first!=b.first.first)return a.first.first>b.first.first;
    return a.first.second<b.first.second;
}
bool cmp2(pair<pair<int,int>,int> a,pair<pair<int,int>,int> b)
{
    if(a.first.second!=b.first.second)return a.first.second<b.first.second;
    return a.first.first>b.first.first;
}
int main()
{
    cin>>N>>W>>H;
    for(int i=1;i<=N;i++)
    {
        int g,p,x=0,y=0,t;
        cin>>g>>p>>t;
        if(g==1)x=p;
        else    y=p;
        V[p-t+100000].push_back({{x,y},i});
    }
    bool ceva=1;
    for(int i=0;i<=200000;i++)
    {
        if(V[i].empty())continue;
        vector<pair<pair<int,int>,int> > tmp;
        for(auto it:V[i])
        {
            if(it.first.first==0)tmp.push_back({{W,it.first.second},0});
            else           tmp.push_back({{it.first.first,H},0});
        }
        sort(tmp.begin(),tmp.end(),cmp1);
        sort(V[i].begin(),V[i].end(),cmp2);
        if(!ceva)
        {
            ceva=1;
            for(auto it:tmp)cout<<it.first.first<<" "<<it.first.second<<"\n";cout<<"\n\n";
            for(auto it:V[i])cout<<it.first.first<<" "<<it.first.second<<"\n";cout<<"\n\n";
        }
        for(int j=0;j<V[i].size();j++)rez[V[i][j].second]=tmp[j].first;
    }
    for(int i=1;i<=N;i++)cout<<rez[i].first<<" "<<rez[i].second<<"\n";
    return 0;
}
