#include <iostream>
#include <cmath>
using namespace std;
int N,M,K;
int A[105];
int minim=(1<<30);
int main()
{
    cin>>N>>M>>K;
    for(int i=1;i<=N;i++)
    {
        cin>>A[i];
        if(A[i]&&abs(i-M)<minim&&A[i]<=K)
            minim=abs(i-M);
    }
    cout<<minim*10;
    return 0;
}
