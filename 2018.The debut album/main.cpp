#include <iostream>
#define MOD 1000000007
using namespace std;
long long A[50005];
long long B[50005];
int N,a,b;
int main()
{
    cin>>N>>a>>b;
    A[1]=B[1]=1;
    A[0]=B[0]=1;
    for(int i=2;i<=N;i++)
    {
        A[i]=(A[i-1]+B[i-1])%MOD;
        B[i]=(A[i-1]+B[i-1])%MOD;
        if(i>a)
            A[i]-=B[i-a-1];
        if(i>b)
            B[i]-=A[i-b-1];
        if(A[i]<0)
            A[i]=A[i]%MOD+MOD;
        if(B[i]<0)
            B[i]=B[i]%MOD+MOD;

    }
    cout<<(A[N]+B[N])%MOD;
    return 0;
}
