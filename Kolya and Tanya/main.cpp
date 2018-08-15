#include <iostream>
using namespace std;
int n,i;
long long rez=1,rele=1;
int main()
{
    cin>>n;
    i=1;
    while(i<=n)
    {
        rez=(rez*27)%1000000007;
        rele=(rele*7)%1000000007;
        i++;
    }
    rez-=rele;
    if(rez<0)
    rez+=1000000007;
    cout<<rez;
    return 0;
}
