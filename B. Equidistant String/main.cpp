#include <iostream>
using namespace std;
string a[2];
string rez;
int l=0;
int main()
{
    cin>>a[0]>>a[1];
    for(int i=0;i<a[0].size();i++)
    {
        if(a[0][i]!=a[1][i])
        {
            rez+=a[l][i];
            l^=1;
        }
        else
            rez+=a[0][i];
    }
    if(l)cout<<"impossible";
    else cout<<rez;
    return 0;
}
