#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
char rez[2000005];
int len,nr,N;
string a[100005];
vector<int> Ev[2000005];
pair<int,int> ev;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>a[i]>>nr;
        for(int j=1;j<=nr;j++)
        {
            int val;cin>>val;
            Ev[val].push_back(i);
            Ev[val+a[i].size()].push_back(-i);
            if(len<val+a[i].size()-1)
                len=val+a[i].size()-1;
        }
    }
    for(int i=1;i<=len;i++)
    {
        for(auto it:Ev[i])
        {
            if(it>0)
            {
                if(i+a[it].size()>ev.second+a[ev.first].size())
                    ev={it,i};
            }
            else
            {
                if(ev==make_pair(-it,int(i-a[-it].size())))
                    ev={0,0};
            }
        }
        if(ev==make_pair(0,0))
        {
            rez[i]='a';
        }
        else
        {
            rez[i]=a[ev.first][i-ev.second];
        }
    }
    cout<<rez+1;
    return 0;
}
