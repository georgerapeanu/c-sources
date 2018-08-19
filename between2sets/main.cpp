#include <iostream>
using namespace std;
int A;
int B;
int a,b;
int c,i;
int N,M,rez=1;
int gcd(int a,int b)
{
    if(!b)
        return a;
    return gcd(b,a%b);
}
int main()
{
    cin>>N>>M;
    a=1;
    for(i=1;i<=N;i++)
    {
        cin>>A;
        c=gcd(A,a);
        a=(A*a)/c;
    }
    for(i=1;i<=M;i++)
    {
        cin>>B;
        b=gcd(b,B);
    }
    if(b%a!=0)
    {
        cout<<0;
        return 0;
    }
    a=b/a;
    for(i=2;i*i<=a;i++)
    {
        int exp=0;
        while(a%i==0)
        {
            exp++;
            a/=i;
        }
        rez*=(exp+1);
    }
    if(a!=1)
        rez*=2;
    cout<<rez;
    return 0;
}
