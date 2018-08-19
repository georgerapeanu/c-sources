#include <iostream>
using namespace std;
int N,K;
int A,v;
int main()
{
    cin>>N>>K;
    for(int i=1;i<=N;i++)
    {
        cin>>v;
        A+=v;
        K-=min(A,8);
        A-=min(A,8);
        if(K<=0){cout<<i;return 0;}
    }
    cout<<-1;
    return 0;
}
