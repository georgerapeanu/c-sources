#include <iostream>
#include <algorithm>
using namespace std;
int B[100005];
long long T;
int N;
int main()
{
    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        int val;
        cin>>val;
        T+=val;
    }
    for(int i=1;i<=N;i++)
        cin>>B[i];
    sort(B+1,B+1+N);
    if(T==1)cout<<"NO";
    else cout<<(B[N]+B[N-1]>=T ? "YES":"NO");
    return 0;
}
