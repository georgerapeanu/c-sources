#include <iostream>
using namespace std;
short f[100000];
int n,i,a[100000],last=1;
int main()
{
    std::cin>>n;
    for(i=1;i<=n;i++)
    {std::cin>>a[i];f[a[i]]=1;}
    for(i=1;i<=n;i++)
    {
        if(a[i]==last)
        {
            last++;
            while(f[last]!=0)
                last++;
        }
        if(f[a[i]]==2||a[i]>n)
        {
            a[i]=last;
            last++;
            while(f[last]!=0)
            last++;
        }
        std::cout<<a[i]<<" ";
        f[a[i]]++;
    }
    return 0;
}
//5 1 5 5 2 1
