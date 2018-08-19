#include <iostream>
#include <iomanip>
using namespace std;
long long A[200005];
long double rez;
int N,K;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N>>K;
    for(int i=1;i<=N;i++)
    {
        cin>>A[i];
        A[i]+=A[i-1];
    }
    for(int i=1;i<=N-K+1;i++)
    {
        rez=rez+1.0*(A[i+K-1]-A[i-1]);
    }
    cout<<fixed<<setprecision(10)<<rez/(N-K+1);
    return 0;
}
