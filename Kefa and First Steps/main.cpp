#include <iostream>
using namespace std;
long n,i,a,fa,o,k;
int main()
{
    cin>>n;k=1;
    for(i=1;i<=n;i++)
    {
        cin>>a;
        if(i>=2)
            if(a>=fa)
            k++;
            else
            {
                o=o>k ? o:k;
                k=1;
            }
        fa=a;
    }
    o=o>k ? o:k;
    cout<<o;
    return 0;
}
