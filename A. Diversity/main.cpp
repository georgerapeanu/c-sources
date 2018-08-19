#include <iostream>
#include <set>
using namespace std;
string a;
int K;
set<char> ceva;
int main()
{
    cin>>a>>K;
    if(a.size()<K)cout<<"impossible";
    else
    {
        for(auto it:a)ceva.insert(it);
        cout<<max(0,K-(int)ceva.size());
    }
    return 0;
}
