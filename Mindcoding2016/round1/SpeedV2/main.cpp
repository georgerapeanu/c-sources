#include <iostream>
using namespace std;
double k1,k2,t1,t2,v2,v1;
int main()
{
    cin>>t1>>k1>>t2>>k2;
    v1=1;
    v2=v1*t1/t2;
    cout<<(v1*t1)/(v1*k1+v2*k2);
    return 0;
}
