#include <iostream>
#include <cmath>
using namespace std;
int a,b;
int x,y;
int main()
{
    cin>>a>>b;
    x=sqrt(a);
    long long st=0,dr=100000;
    while(st<dr)
    {
        long long mid=(1+st+dr)/2;
        if(mid*(mid+1)<=b)
            st=mid;
        else
            dr=mid-1;
    }
    y=st;
    cout<<(x>y ? "Valera":"Vladik");
    return 0;
}
