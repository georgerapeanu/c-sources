#include <iostream>
using namespace std;
long long N,K,t;
int main()
{
    cin>>N>>K;
    t=N/K;
    if(t%2==1)cout<<"YES";
    else cout<<"NO";
    return 0;
}
