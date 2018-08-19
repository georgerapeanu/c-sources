#include <iostream>
using namespace std;
int a,b,r;
int rez;
int main()
{
    cin>>a>>b;
    while(a)
    {
        rez+=a;
        r+=a%b;
        a=a/b+r/b;
        r%=b;
    }
    cout<<rez;
    return 0;
}
