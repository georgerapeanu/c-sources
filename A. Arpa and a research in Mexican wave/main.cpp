#include <iostream>
using namespace std;
long long N,K,T;
int main()
{
    cin>>N>>K>>T;
    if(T<=K)cout<<T;
    else if(T>N)cout<<K-(T-N);
    else cout<<K;
    return 0;
}
