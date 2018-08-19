#include <iostream>
using namespace std;
long long minim=101,a,p,s,n,i;
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>a>>p;
        if(minim>p)
        minim=p;
        s+=minim*a;
    }
    cout<<s;
    return 0;
}
