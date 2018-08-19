#include <iostream>
using namespace std;
string S;
int st,dr,rez;
int main()
{
    cin>>S;
    for(auto it:S)
        dr+=(it=='Q');
    for(auto it:S)
    {
        if(it=='A')
        {
            rez+=st*dr;
        }
        else if(it=='Q')
        {
            st++;
            dr--;
        }
    }
    cout<<rez;
    return 0;
}
