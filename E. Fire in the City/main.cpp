#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
using namespace std;
struct data
{
    int st,dr;
    bool t;
    bool operator <(const data &other)const
    {
        if(st!=other.st)return st<other.st;
        if(dr!=other.dr)return dr<other.dr;
        return t<other.t;
    }
};
map<int,vector<data> > V;
pair<int,int> P[505];
int K;
int N,M;
multiset<pair<int,int> > S;
pair<int,int> gety(int val)
{
    V.clear();S.clear();
    pair<int,int> rez={1<<30,0};
    for(int i=1;i<=K;i++)
    {
        V[max(1,P[i].first-val)].push_back({max(1,P[i].second-val),min(M,P[i].second+val),0});
        V[min(N,P[i].first+val)+1].push_back({max(1,P[i].second-val),min(M,P[i].second+val),1});
    }
    int last=0;
    for(auto it:V)
    {
        if(it.first==N+1)break;
        if(it.first!=last+1&&S.empty())return {1,M};
        for(auto it2:it.second)
        {
            if(it2.t)S.erase(S.find({it2.st,it2.dr}));
            else     S.insert({it2.st,it2.dr});
        }
        last=it.first;
        int x=1;
        for(auto it:S)
        {
            if(it.first<=x&&x<=it.second)x=it.second+1;
        }
        if(x<=M)rez.first=min(rez.first,x);
        x=M;
        for(multiset<pair<int,int> > ::reverse_iterator it=S.rbegin();it!=S.rend();it++)
        {
            if(it->second>=x&&it->first<=x)x=it->first-1;
        }
        if(x>0)rez.second=max(x,rez.second);
    }
    if(rez!=make_pair(1<<30,0))return rez;
    return {0,0};
}
pair<int,int> getx(int val)
{
    V.clear();S.clear();
    pair<int,int> rez={1<<30,0};
    for(int i=1;i<=K;i++)
    {
        V[max(1,P[i].second-val)].push_back({max(1,P[i].first-val),min(N,P[i].first+val),0});
        V[min(M,P[i].second+val)+1].push_back({max(1,P[i].first-val),min(N,P[i].first+val),1});
    }
    int last=0;
    for(auto it:V)
    {
        if(it.first==M+1)break;
        if(it.first!=last+1&&S.empty())return {1,N};
        for(auto it2:it.second)
        {
            if(it2.t)S.erase(S.find({it2.st,it2.dr}));
            else     S.insert({it2.st,it2.dr});
        }
        last=it.first;
        int x=1;
        for(auto it:S)
        {
            if(it.first<=x&&x<=it.second)x=it.second+1;
        }
        if(x<=N)rez.first=min(rez.first,x);
        x=N;
        for(multiset<pair<int,int> > ::reverse_iterator it=S.rbegin();it!=S.rend();it++)
        {
            if(it->second>=x&&it->first<=x)x=it->first-1;
        }
        if(x>0)rez.second=max(x,rez.second);
    }
    if(rez!=make_pair(1<<30,0))return rez;
    return {0,0};
}
bool check(int val)
{
    pair<int,int> fst=gety(val);
    pair<int,int> snd=getx(val);
    if(fst.second-fst.first+1<=2*val+1&&snd.second-snd.first+1<=2*val+1)return 1;
    return 0;
}
int main()
{
    bool deg=0;
    if(deg)
    {
        N=6;
        M=6;
        K=3;
        P[1]={2,2};
        P[2]={5,2};
        P[3]={5,4};
        pair<int,int> tmp=getx(2);
        cout<<tmp.first<<" "<<tmp.second;
    }
    cin>>N>>M>>K;
    for(int i=1;i<=K;i++)cin>>P[i].first>>P[i].second;
    int st=0,dr=1000000000;
    while(st<dr)
    {
        int mid=(0LL+st+dr)/2;
        if(check(mid))dr=mid;
        else st=mid+1;
    }
    cout<<st;
    return 0;
}
