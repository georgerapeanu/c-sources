#include <iostream>
#include <cstdio>
#include <iomanip>
using namespace std;
int T;
long double N,D;
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    cin>>T;
    for(int i=1;i<=T;i++)
    {
        cin>>D>>N;
        long double val=0;
        for(int i=1;i<=N;i++)
        {
            long double K,S;
            cin>>K>>S;
            val=max((D-K)/S,val);
        }
        cout<<"Case #"<<i<<": "<<fixed<<setprecision(10)<<D/val<<"\n";
    }
    return 0;
}
