#include<iostream>
using namespace std;
int main()
{
    int x,y,n,s;
    cout<<"y=";
    cin>>y;
    n=2500;
    x=0;
    s=0;
    while(x<=y)
    {
        if(x%2!=0)
            {
                s=s+x;
            }
        x=x+1;

    }
    if(n==s)
        cout<<"1";
    else
        cout<<"0";
    return 0;
}
