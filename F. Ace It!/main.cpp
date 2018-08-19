#include <iostream>
using namespace std;
string a;
int nr;
int main()
{
    cin>>a;
    for(auto it:a)
    {
        if(it=='A')nr+=1;
        else if(it!='1')nr+=it-'0';
        else nr+=10;
    }
    cout<<nr;
    return 0;
}
