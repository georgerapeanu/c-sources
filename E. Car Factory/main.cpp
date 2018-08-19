#include <iostream>

using namespace std;
int T,N,K;
int main()
{
    cin>>T;
    while(T--)
    {
        cin>>N>>K;
        cout<<(long long)N+K-1<<"\n";
    }
    return 0;
}
