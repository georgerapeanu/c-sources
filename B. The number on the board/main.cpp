#include <iostream>
#include <algorithm>
using namespace std;
string n;
int k,s,nr;
int main()
{
    cin>>k>>n;
    sort(n.begin(),n.end());
    for(auto it:n)s+=it-'0';
    for(auto it:n)
    {
        if(k<=s)break;
        nr++;
        s+='9'-it;
    }
    cout<<nr;
    return 0;
}
