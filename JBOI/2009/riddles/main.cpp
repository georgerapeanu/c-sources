#include <iostream>
#include <algorithm>
using namespace std;
int A[100005];
int V[100005];
int N,K,T;
int ok(int n)
{
    for(int i=1;i<=n;i++)V[i]=A[i];sort(V+1,V+1+n);
    int sum=0;
    for(int i=1;i<=n;i++)
    {
        if(sum+1<V[i])return 0;
        sum+=V[i];if(sum>=K)return 1;
    }
    return 0;
}
int main()
{
    cin>>T;
    while(T--)
    {
        cin>>N>>K;
        for(int i=1;i<=N;i++)cin>>A[i];
        int st=1,dr=N+1;
        while(st<dr)
        {
            int mid=(st+dr)/2;
            if(ok(mid))dr=mid;
            else st=mid+1;
        }
        cout<<(dr==N+1 ? -1:dr)<<"\n";
    }
    return 0;
}
