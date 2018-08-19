#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
using namespace std;
set<int> SX,SY;
map<int,vector<pair<int,int> > >X,Y;
int x,y,l;
int N,nr;
bool conectate(vector<pair<int,int> > V,int st,int dr)
{
    for(auto it:V)
    {
        if(it.first<=st&&st<=it.second)st=it.second;
        if(st>=dr)return 1;
    }
    return 0;
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>x>>y>>l;
        SX.insert(x);SY.insert(y);
        SX.insert(x+l);SY.insert(y+l);
        X[x].push_back({y,y+l});
        X[x+l].push_back({y,y+l});
        Y[y].push_back({x,x+l});
        Y[y+l].push_back({x,x+l});
    }
    for(auto &it:X)sort(it.second.begin(),it.second.end());
    for(auto &it:Y)sort(it.second.begin(),it.second.end());
    for(set<int>::iterator it=SX.begin();it!=SX.end();it++)
    {
        for(set<int >::iterator it2=SY.begin();it2!=SY.end();it2++)
        {
            set<int >::iterator it3=it;it3++;
            for(;it3!=SX.end();it3++)
            {
                if(SY.find(*it2+*it3-*it)!=SY.end())
                {
                    int x=*it,y=*it2,xx=*it3,yy=*it2+*it3-*it;
                    if(conectate(X[x],y,yy)&&conectate(X[xx],y,yy)&&conectate(Y[y],x,xx)&&conectate(Y[yy],x,xx))
                        nr++;
                }
            }
        }
    }
    cout<<nr;
    return 0;
}
