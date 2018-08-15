#include <iostream>
#include <cstdio>
using namespace std;
int N,M,P,A,B;
int main()
{
    freopen("gusteri.in","r",stdin);
    freopen("gusteri.out","w",stdout);
    cin>>N>>P>>M>>A>>B;
    for(int i=1;i<=B;i++)
    {
        if(i>=A)cout<<N<<"\n";
        N=(1LL*N*P)%M;
    }
    return 0;
}
