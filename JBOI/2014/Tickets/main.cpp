#include <iostream>

using namespace std;
int N;
long long K;
string f(int n,long long k)
{
    if(n==0)return "";
    if(k>(1LL<<(n-1)))
        return "1"+f(n-1,(1LL<<n)-k+1);
    else
        return "0"+f(n-1,k);
}
int main()
{
    cin>>N>>K;
    cout<<f(N,K);
    return 0;
}
