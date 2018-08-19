#include <iostream>
#include <bitset>
using namespace std;
int T,K,L;
int N;
bitset<1000005> B;
int main()
{
    cin>>K>>L>>T;
    for(int i=1;i<=1000005;i++)
        if(!B[i-1]||(i>=K&&!B[i-K])||(i>=L&&!B[i-L]))B[i]=1;
        else B[i]=0;
    for(int i=1;i<=T;i++)
    {
        cin>>N;
        cout<<(char)(!B[N]+'A');
    }
    return 0;
}
