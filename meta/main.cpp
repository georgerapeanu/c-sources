#include <iostream>
using namespace std;
long long MOD1,MOD2,val,a,b,r;
int main()
{
    cin>>MOD1>>MOD2;
    a=MOD1;
    b=MOD2;
    r=a%b;
    while(r)
    {
        a=b;
        b=r;
        r=a%b;
    }
    val=1+(MOD1*MOD2/b);
    cout<<2<<"\n";
    cout<<1<<" "<<val<<"\n";
    cout<<3<<" "<<1;
    return 0;
}