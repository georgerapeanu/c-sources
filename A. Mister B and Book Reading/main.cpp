#include <iostream>
using namespace std;
int a,c,v0,v1,l;
int upag;
int main()
{
    cin>>c>>v0>>v1>>a>>l;
    int rez=0;
    while(c>upag)
    {
        if(rez>0)
        {
            upag=upag-l;
        }
        upag+=v0;
        v0=min(v1,v0+a);
        rez++;
    }
    cout<<rez;
    return 0;
}
