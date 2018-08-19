#include <iostream>
using namespace std;
int N,K,X;
int A[105];
int rez;
int main()
{
    cin>>N>>K>>X;
    for(int i=1;i<=N;i++)
    {
        cin>>A[i];
    }
    for(int i=1;i<=N-K;i++)rez+=A[i];
    for(int i=N-K+1;i<=N;i++)rez+=min(X,A[i]);
    cout<<rez;
    return 0;
}
