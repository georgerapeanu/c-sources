#include <iostream>
#include <iomanip>
using namespace std;
int z;
int R[17];
int M[17];
int N,zi;
int nr;
int gcd(int a,int b)
{
    if(!b)return a;
    return gcd(b,a%b);
}
int lcm(int a,int b)
{
    if(!a)return b;
    if(!b)return a;
    return 1LL*a*b/gcd(a,b);
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)cin>>M[i];
    for(int i=1;i<=N;i++)cin>>R[i];
    for(int i=1;i<=N;i++)zi=lcm(zi,M[i]);
    for(int i=0;i<zi;i++)
    {
        bool ok=0;
        for(int j=1;j<=N;j++)
            if(i%M[j]==R[j])
                ok=1;
        nr+=ok;
    }
    cout<<fixed<<setprecision(10)<<1.0*nr/(zi);
    return 0;
}
