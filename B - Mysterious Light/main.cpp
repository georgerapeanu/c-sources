#include <iostream>
#include <algorithm>
using namespace std;
long long N,X;
long long solve(long long a,long long b)
{
    if(a%b==0) return ((a/b)*2-1)*b;
    if(!b)return 0;
    return 2*b*(a/b)+solve(b,a%b);
}
int main()
{
    cin>>N>>X;
    long long a=X,b=N-X;
    if(a<b)swap(a,b);
    cout<<N+solve(a,b);
    return 0;
}
