#include <iostream>
#include <cstdio>
using namespace std;
int N;
int A[100005];
int nr;
int gcd(int a,int b)
{
    if(!b)return a;
    return gcd(b,a%b);
}
int main()
{
    cin>>N;
    int g=0;
    for(int i=1;i<=N;i++)
    {
        cin>>A[i];
        g=gcd(g,A[i]);
        A[i]%=2;
    }
    if(g!=1){cout<<"YES\n0";return 0;}
    for(int i=1;i<N;i++)
    {
        if(A[i]%2==0)continue;
        if(A[i]%2==A[i+1]%2)
            {nr++;A[i+1]=0;}
        else
        {
            nr+=2;
        }
    }
    if(A[N]%2==1)
    {
        nr+=2;
    }
    cout<<"YES\n"<<nr;
    return 0;
}
