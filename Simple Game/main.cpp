#include <iostream>
#include <cmath>
using namespace std;
int n,m;
double a,b;
int main()
{
    std::cin>>n>>m;
    a=double(m-1)/n;
    b=double(n-m)/n;
    if(n==1)
    std::cout<<1;
    else
    {
        if(a>=b)
        std::cout<<m-1;
        else
        cout<<m+1;
    }
    return 0;
}
