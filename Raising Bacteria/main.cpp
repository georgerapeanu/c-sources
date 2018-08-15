#include <iostream>
using namespace std;
long long x,nr;
int main()
{
    cin>>x;
    while(x!=0)
    {
        if(x%2==1)
        nr++;
        x/=2;
    }
    cout<<nr;
    return 0;
}
