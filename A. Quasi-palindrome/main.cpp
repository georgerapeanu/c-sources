#include <iostream>

using namespace std;
string a;
int main()
{
    cin>>a;
    int dr=a.size()-1;
    while(a[dr]=='0'&&dr)dr--;
    int st=0;
    while(st<dr)
    {
        if(a[st]!=a[dr]){cout<<"NO";return 0;}
        st++;dr--;
    }
    cout<<"YES";
    return 0;
}
