#include <iostream>
#include <cmath>
using namespace std;
long long n,x,i,nr,st,fn;
int main()
{
    cin>>n>>x;
    if(x%n==0)
    st=x/n;
    else
    st=x/n+1;
    if(sqrt(x)<n)
    fn=sqrt(x);
    else
    fn=n;
    for(i=st;i<=fn;i++)
    {
        if(x%i==0)
        {
            nr++;
            if(x/i!=i)
            nr++;
        }
    }
    cout<<nr;
    return 0;
}
