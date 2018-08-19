#include <iostream>
using namespace std;
string a;
int rez;
int main()
{
    cin>>a;
    for(auto it:a)
    {
        if('a'<=it&&it<='z')rez-=it-'a'+1;
        else if('A'<=it&&it<='Z')rez+=it-'A'+1;
    }
    cout<<rez;
    return 0;
}
