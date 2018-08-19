#include <iostream>

using namespace std;
long long a,b,k;
int main()
{
    cin>>k>>a>>b;
    if(a>b)
        swap(a,b);
    if(a>=k&&b>=k) cout<<(a/k+b/k);
    else if(b%k==0&&a<=(b/k)*(k-1)) cout<<b/k;
    else cout<<-1;
    return 0;
}
