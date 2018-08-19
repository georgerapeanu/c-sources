#include <iostream>
#include <algorithm>
using namespace std;
int s,t,x,rez=1<<30;
vector<int> V;
void ins(int val)
{
    if(V.empty()||V.back()!=val)
        V.push_back(val);
}
void solve(int div)
{
    if(div<x)
        return ;
    if(rez>abs(x-s)+min(div%x,x-div%x))
    {
        V.clear();
        ins(s);
        ins(x);
        if(div>=x&&div%x<x-div%x)
        {
            ins(div-div%x);
        }
        else
        {
            ins(div+x-div%x);
        }
        ins(div);
        ins(t);
        rez=abs(x-s)+min(div%x,x-div%x);
    }
}
int main()
{
    cin>>s>>t;
    V.clear();
    for(x=1;x<=16;x++)
    {
        for(int j=1;j*j<=t;j++)
        {
            if(t%j==0)
            {
                solve(j);
                solve(t/j);
            }
        }
    }
    cout<<rez<<"\n";
    cout<<V.size()<<"\n";
    for(auto it:V)
        cout<<it<<" ";
    return 0;
}
