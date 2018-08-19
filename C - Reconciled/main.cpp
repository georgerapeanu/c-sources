#include <iostream>
#define MOD 1000000007
using namespace std;
int N,M;
int rez=1;
int main()
{
    cin>>N>>M;
    if(N>M)swap(N,M);
    if(M-N>1){cout<<0;return 0;}
    if(M==N)rez=2;
    int fa=1;
    for(int i=1;i<=M;i++)
    {
        fa=(1LL*fa*i)%MOD;
        if(i==N)rez=(1LL*fa*rez)%MOD;
        if(i==M)rez=(1LL*fa*rez)%MOD;
    }
    cout<<rez;
    return 0;
}
