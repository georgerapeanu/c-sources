#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
long long A[100005];
long long B[100005];
long long V[100005];
set<int> S;
long long N,M,K;
int main()
{
    cin>>N>>M>>K;
    for(long long i=1;i<=N;i++){cin>>V[i];V[i]=(M-V[i])/K+1;}
    A[1]=V[1];
    B[N]=V[N];
    for(long long i=2;i<=N;i++)A[i]=abs(A[i-1]-V[i]);
    for(long long i=N-1;i;i--)B[i]=abs(B[i+1]-V[i]);
    for(long long i=1;i<=N;i++)
    {
        long long tmp=min(A[i-1],B[i+1]);
        long long nr=abs(V[i]-(A[i-1]-tmp)-(B[i+1]-tmp));
        S.insert(nr);
    }
    cout<<S.size();
    return 0;
}
