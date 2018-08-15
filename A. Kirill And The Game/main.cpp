#include <iostream>

using namespace std;
long long l,r,x,y,k;
int main()
{
    cin>>l>>r>>x>>y>>k;
    for(int b=x;b<=y;b++)
    {
        if(l<=1LL*b*k&&1LL*b*k<=r){cout<<"YES";return 0;}
    }
    cout<<"NO";
    return 0;
}
