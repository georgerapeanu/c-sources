#include <iostream>

using namespace std;
string a;
string b="FESTIVAL";
int main()
{
    cin>>a;
    while(b.size())
    {
        b.pop_back();
        a.pop_back();
    }
    cout<<a;
    return 0;
}
