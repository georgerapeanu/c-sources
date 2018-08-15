#include <iostream>
#include <algorithm>
using namespace std;
int A[200005];
pair<int,int> B[200005];
int rez[200005];
int N;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N;
    for(int i=1;i<=N;i++)cin>>A[i];
    for(int i=1;i<=N;i++){cin>>B[i].first;B[i].second=i;}
    sort(A+1,A+1+N);reverse(A+1,A+1+N);
    sort(B+1,B+1+N);
    for(int i=1;i<=N;i++)rez[B[i].second]=A[i];
    for(int i=1;i<=N;i++)cout<<rez[i]<<" ";
    return 0;
}
