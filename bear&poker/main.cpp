#include <iostream>
#define ull unsigned long long
using namespace std;
ull gcd,a[100001],i,n,nr;
bool gasit=1;
ull GCD(ull x,ull y)
{
    if(y==0) return x;
    return GCD(y,x%y);
}
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>a[i];
        gcd=GCD(gcd,a[i]);
    }
    for(i=1;i<=n;i++)
    {
        nr=a[i]/gcd;
        while(nr%2==0)
        nr/=2;
        while(nr%3==0)
        nr/=3;
        if(nr!=1)
        {
            gasit=0;break;
        }
    }
    if(gasit==1)
    cout<<"Yes";
    else
    cout<<"No";
}
