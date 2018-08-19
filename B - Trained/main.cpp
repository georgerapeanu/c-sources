#include <iostream>
#include <bitset>
using namespace std;
int N,A[100005];
bitset<100005> B;
int nr;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)cin>>A[i];
    nr=0;
    int b=1;
    while(b!=2)
    {
        nr++;
        if(B[b]){cout<<-1;return 0;}
        B[b]=1;
        b=A[b];
    }
    cout<<nr;
    return 0;
}
