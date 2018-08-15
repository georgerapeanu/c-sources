#include <iostream>
using namespace std;
bool ap[1000001];
long a;
int nr,n,i,maxim;
char c;
int main()
{
    std::cin>>n;
    for(i=1;i<=n;i++)
    {
        std::cin>>c;
        std::cin>>a;
        if(c=='+')
        {
            nr++;
            ap[a]=1;
        }
        else
        {
            if(ap[a]==0)
            maxim++;
            else
            nr--;
        }
        if(nr>maxim)
        maxim=nr;
    }
    std::cout<<maxim;
    return 0;
}
