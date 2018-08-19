#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int fst[100005];
int lst[100005];
int N,M;
int rez;
vector<pair<int,int> > V;
int dfs(pair<int,int> a,int &ind,int base)
{
    vector<int> tmp;tmp.clear();
    int rez=0;
    while(ind<V.size()&&a.first<=V[ind].first&&a.second>=V[ind].second)
    {
        tmp.push_back(ind);
        ind++;
        dfs(V[ind-1],ind,base);
    }
    if(tmp.empty())return base;
    int sz=0;
    for(int l=0,r=-1;l<tmp.size();l++)
    {
        if(l>r)
        {
            r=l;
            sz=1;
            while(r<tmp.size()-1&&V[tmp[r+1]].first==V[tmp[r]].second+1){r++;sz++;}
        }
        int t=tmp[l]+1;
        rez=max(rez,dfs(V[t-1],t,base+sz));

    }
    return rez;
}
int main() {
    cin>>N>>M;
    for(int i=1;i<=N;i++)
    {
        int val;
        cin>>val;
        if(!fst[val])fst[val]=i;
        lst[val]=i;
    }
    for(int i=1;i<=M;i++)
    {
        if(fst[i]==0)rez++;
        else V.push_back({fst[i],lst[i]});
    }
    sort(V.begin(),V.end());
    for(int i=1;i<V.size();i++)
    {
        //cerr<<V[i].first<<" "<<V[i].second<<"\n";
        if((V[i-1].first<=V[i].first&&V[i].second<=V[i-1].second)||(V[i-1].second<V[i].first))continue;
        cout<<-1;
        return 0;
    }
    int ind=0;
    cout<<dfs({0,N+1},ind,rez);
    return 0;
}
