#include <iostream>
using namespace std;
long na,nb,a,b,k,m,i,nr;
int main()
{
    std::cin>>na>>nb>>k>>m;
    for(i=1;i<=na;i++)
    {
        std::cin>>nr;
        if(i==k)
        a=nr;
    }
    for(i=1;i<=nb;i++)
    {
        std::cin>>nr;
        if(i==nb-m+1)
        b=nr;
    }
    if(a<b)
    std::cout<<"YES";
    else
    std::cout<<"NO";
    return 0;
}
