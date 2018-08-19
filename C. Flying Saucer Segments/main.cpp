#include <iostream>

using namespace std;
int N,M;
long long lpow(long long b,int e)
{
    if(!e) return 1;
    if(e&1) return (b*lpow((b*b)%M,e/2))%M;
    return lpow((b*b)%M,e/2)%M;
}
int main()
{
    cin>>N>>M;
    cout<<(lpow(3LL,N)+M-1)%M;
    return 0;
}
