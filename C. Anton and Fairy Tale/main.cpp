#include <iostream>
#define ULL unsigned long long
using namespace std;
ULL k,st,dr;
ULL N,M;
int main()
{
    cin>>N>>M;
    if(N<=M)
    {cout<<N;return 0;}
    N=N-M;
    st=1,dr=1500000000;
    while(st<dr)
    {
        ULL mid=(st+dr)/2;
        if(mid*(mid+1)/2>=N)
            dr=mid;
        else
            st=mid+1;
    }
    cout<<M+st;
    return 0;
}
