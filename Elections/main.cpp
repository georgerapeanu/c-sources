#include <iostream>
using namespace std;
long long n,m,v[101],i,j,vot,maxvot,index;
int main()
{
    std::cin>>n>>m;
    for(i=1;i<=m;i++)
    {
        maxvot=-1;index=0;
        for(j=1;j<=n;j++)
        {
            std::cin>>vot;
            if(maxvot<vot)
            {maxvot=vot;index=j;}
        }
        v[index]++;
    }
    maxvot=-1;index=0;
    for(i=1;i<=n;i++)
    {
        if(v[i]>maxvot)
        {
            maxvot=v[i];
            index=i;
        }
    }
    std::cout<<index;
    return 0;
}
