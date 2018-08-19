#include <iostream>
#define LL long long
using namespace std;
LL N,val;
LL q(LL nr)
{
    int lg=0;
    while((1LL<<lg)<=nr)
        lg++;
    lg--;
    LL rez=nr;
    for(int i=0;i<lg;i++)
        for(int j=0;j<lg;j++)
            rez=max(rez,nr-(nr&(1<<i))+((nr&(1<<j))!=0)*(1<<i)-(nr&(1<<j))+((nr&(1<<i))!=0)*(1<<j));
    return rez;
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>val;
        cout<<q(val)<<" ";
    }
    return 0;
}
