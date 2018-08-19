#include <iostream>
using namespace std;
int V,n,i,val,pasi;
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>V;
        if(val>=V)
        {
            pasi+=val-V;
            val=V;
        }
        else
        {
            pasi+=V-val;
            val=V;
        }
    }
    cout<<pasi;
    return 0;
}
