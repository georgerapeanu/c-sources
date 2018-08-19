#include <iostream>
using namespace std;
int N,M,Z;
int gcd(int a,int b)
{
    if(!b) return a;
    return gcd(b,a%b);
}
int main()
{
    cin>>N>>M>>Z;
    cout<<(Z/(N*M/gcd(N,M)));
    return 0;
}
