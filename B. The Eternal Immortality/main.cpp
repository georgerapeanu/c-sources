#include <iostream>
using namespace std;
long long a,b;
int rez;
int main()
{
    cin>>a>>b;
    if(b-a>=10)
    {
        cout<<0;
        return 0;
    }
    rez=1;
    for(long long i=a+1;i<=b;i++)
        rez=(1LL*rez*i)%10;
    cout<<rez;
    return 0;
}
