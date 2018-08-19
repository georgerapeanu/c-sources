#include <iostream>
#include <algorithm>
using namespace std;
long long V[100005];
long long N,X,K;
long long rez=0;
int main()
{
    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);
    cin>>N>>X>>K;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i];
    }
    sort(V+1,V+1+N);
    for(int i=1;i<=N;i++)
    {
        long long st=X*(K+(V[i]-1)/X);
        long long dr=st+X;
        st=max(st,V[i]);
        rez+=lower_bound(V+1,V+1+N,dr)-lower_bound(V+1,V+1+N,st);
    }
    cout<<rez;
    return 0;
}
