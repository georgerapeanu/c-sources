#include <iostream>
using namespace std;
long long N,s;
long long a,b,c;
int nr;
int main()
{
    cin>>N;
    a=1;
    b=1;
    s=1;
    while(s<N)
    {
        s+=b;
        nr++;
        c=a;
        a=b;
        b+=c;
    }
    cout<<nr;
    return 0;
}
