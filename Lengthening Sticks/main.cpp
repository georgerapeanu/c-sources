#include <iostream>
using namespace std;
long long var,a,b,c,la,lb,lc,l,rele,x;
long long min(long long x,long long y)
{
    if(x<y)
    return x;
    return y;
}
int main()
{
    cin>>a>>b>>c>>l;
    var=(l+1)*(l+2)*(l+3)/6;
    for(la=0;la<=l;la++)
    {
        x=min(l-la,a-b-c+la);
        if(x>=0)
        rele+=(x+1)*(x+2)/2;
    }
    for(lb=0;lb<=l;lb++)
    {
        x=min(l-lb,b-a-c+lb);
        if(x>=0)
        rele+=(x+1)*(x+2)/2;
    }
    for(lc=0;lc<=l;lc++)
    {
        x=min(l-lc,c-b-a+lc);
        if(x>=0)
        rele+=(x+1)*(x+2)/2;
    }
    cout<<(var-rele);
}
