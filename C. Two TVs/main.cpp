#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N;
vector<pair<int,int> > Ev;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        int x,y;
        cin>>x>>y;
        Ev.push_back({x,-1});
        Ev.push_back({y,1});
    }
    int act=0;
    sort(Ev.begin(),Ev.end());
    for(auto it:Ev)
    {
        act-=it.second;
        if(act>2){cout<<"NO";return 0;}
    }
    cout<<"YES";
    return 0;
}
