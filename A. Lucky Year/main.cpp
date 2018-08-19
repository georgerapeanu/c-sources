#include <iostream>
using namespace std;
long long N;
long long p10=1;
int main()
{
    cin>>N;
    while(p10*10<=N)p10*=10;
    long long nxt=N-N%p10+p10;
    cout<<nxt-N;
    return 0;
}
