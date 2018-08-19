#include <iostream>
#include <vector>
using namespace std;
vector<int> V;
void solve(int len)
{
    if(len==2)
    {
        V.push_back(1);V.push_back(2);V.push_back(1);return ;
    }
    if(len==3)
    {
        V.push_back(2);
        V.push_back(3);
        V.push_back(1);
        V.push_back(2);
        return ;
    }
    V.push_back(len-1);
    V.push_back(len);
    solve(len-2);
    V.push_back(len-1);
}
int N;
int main()
{
    cin>>N;
    solve(N);
    cout<<V.size()<<"\n";
    for(auto it:V)cout<<it<<" ";
    return 0;
}
