#include <iostream>
using namespace std;
int N,K;
int A[100005];
int nr=0;
int gcd(int a,int b)
{
    if(!b)return a;
    return gcd(b,a%b);
}
int main()
{
    cin>>N>>K;
    for(int i=1;i<=N;i++)
    {
        cin>>A[i];
        nr=gcd(nr,A[i]);
    }
    for(int i=1;i<=N;i++)
    {
        if(A[i]>=K&&(A[i]-K)%nr==0)
        {
            cout<<"POSSIBLE";return 0;
        }
    }
    cout<<"IMPOSSIBLE";return 0;
    return 0;
}
