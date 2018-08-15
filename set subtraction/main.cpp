#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
pair<int,int> V[1000005];
int A[1000005];
bool ok[1000005];
long long sum[1000005];
set<int> S;
int N,D;
int main() {
    cin>>N>>D;
    ok[0]=1;ok[N+1]=1;
    S.insert(0);
    S.insert(N+1);
    for(int i=1;i<=N;i++)
    {
        cin>>V[i].first;V[i].second=i;
        A[i]=V[i].first;
        sum[i]+=V[i].first;
    }
    for(int i=1;i<=N;i++)sum[i]+=sum[i-1];
    sort(V+1,V+1+N);
    for(int i=N;i;i--)
    {
        set<int>::iterator it=S.lower_bound(V[i].second);
        int dr=*it;it--;
        int st=*it;
        if(sum[dr-1]-sum[st]+D>=A[st]&&ok[st])
        {
            ok[V[i].second]=1;
        }
        else if(sum[dr-1]-sum[st]+D>=A[dr]&&ok[dr])
        {
            ok[V[i].second]=1;
        }
        S.insert(V[i].second);
    }
    for(int i=1;i<=N;i++)if(ok[i])cout<<i<<" ";
    return 0;
}
