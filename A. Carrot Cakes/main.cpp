#include <iostream>
using namespace std;
int a;
int N,T,K,D;
int main()
{
    cin>>N>>T>>K>>D;
    if((N/K+(N%K!=0))*T>D+max(0,T*((N-D/T*K)/(2*K)+((N-D/T*K)%(2*K)!=0))))
        cout<<"YES";
    else
        cout<<"NO";
    return 0;
}
