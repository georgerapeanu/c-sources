#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int x,y,N;
int rez;
vector<pair<int,pair<int,int> > > V;
vector<pair<int,int> > X,Y;
int T[100005];
int fi(int x)
{
    if(T[x]<0)return x;
    return T[x]=fi(T[x]);
}
void u(int x,int y,int cost)
{
    x=fi(x);
    y=fi(y);
    if(x==y)return ;
    rez+=cost;
    if(T[x]<T[y]){T[x]+=T[y];T[y]=x;}
    else {T[y]+=T[x];T[x]=y;}
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        T[i]=-1;
        cin>>x>>y;
        X.push_back(make_pair(x,i));
        Y.push_back(make_pair(y,i));
    }
    sort(X.begin(),X.end());
    sort(Y.begin(),Y.end());
    for(int i=0;i<N-1;i++)
    {
        V.push_back(make_pair(X[i+1].first-X[i].first,make_pair(X[i].second,X[i+1].second)));
        V.push_back(make_pair(Y[i+1].first-Y[i].first,make_pair(Y[i].second,Y[i+1].second)));
    }
    sort(V.begin(),V.end());
    for(auto it:V)
    {
        u(it.second.first,it.second.second,it.first);
    }
    cout<<rez;
    return 0;
}
