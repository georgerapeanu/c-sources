#include <iostream>
using namespace std;
int n,t,i;
int main()
{
    cin>>n>>t;
    if(t==10)
    {
        if(n==1)
        cout<<-1;
        else
        {
            cout<<10;
            for(i=1;i<=n-2;i++)
            cout<<0;
        }
    }
    else
    {
        for(i=1;i<=n;i++)
        cout<<t;
    }
    return 0;
}