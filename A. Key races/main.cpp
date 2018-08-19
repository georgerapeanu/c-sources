#include <iostream>
using namespace std;
int s,v1,v2,t1,t2;
int main()
{
    cin>>s>>v1>>v2>>t1>>t2;
    if(2*t1+v1*s<2*t2+v2*s)cout<<"First";
    else if(2*t1+v1*s>2*t2+v2*s)cout<<"Second";
    else cout<<"Friendship";
    return 0;
}
