#include <iostream>
#include <bitset>
using namespace std;
bitset<1000005> B;
int N,M,K;
int x=1;
int st,dr;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N>>M>>K;
    for(int i=1;i<=M;i++)
    {
        cin>>x;
        B[x]=1;
    }
    x=1;
    for(int i=1;i<=K;i++)
    {
        cin>>st>>dr;
        if(B[x]) continue;
        if(dr==x) x=st;
        else if(st==x) x=dr;
    }
    cout<<x;
    return 0;
}
