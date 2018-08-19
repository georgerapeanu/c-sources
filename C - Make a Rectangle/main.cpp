#include <iostream>
#include <algorithm>
using namespace std;
int N;
int A[100005];
int ind;
int a,b;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)cin>>A[i];
    sort(A+1,A+1+N);
    ind=N;
    while(ind&&A[ind]!=A[ind-1])ind--;
    if(!ind){cout<<0;return 0;}
    a=A[ind];
    swap(A[ind],A[N]);
    swap(A[ind-1],A[N-1]);
    N-=2;
    sort(A+1,A+1+N);
    ind=N;
    while(ind&&A[ind]!=A[ind-1])ind--;
    if(!ind){cout<<0;return 0;}
    b=A[ind];
    cout<<1LL*a*b;
    return 0;
}
