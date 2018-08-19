#include <iostream>

using namespace std;
int N,K;
int V[100005];
int tmp[100005];
int sz;
bool ok(int dif)
{
    sz=0;
    int nK=K;
    for(int i=1;i<=N-nK&&nK>=0;i++)
    {
        if(V[i]-V[i-1]>dif)
        {
            nK-=sz;
            sz=0;
        }
        sz++;
    }
    return nK>=0;
}
int main() {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N>>K;
    for(int i=1;i<=N;i++)cin>>V[i];
    V[0]=V[1];
    long long st=-2000000000,dr=2000000000;
    while(st<dr)
    {
        int mid=(dr+st)>>1;
        if(ok(mid))dr=mid;
        else st=mid+1;
    }
    cout<<st;
    return 0;
}
