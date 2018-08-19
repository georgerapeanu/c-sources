#include <iostream>
#include <algorithm>
using namespace std;
long long maxdistance=-1,a,b,i,j;
long long gcd(long long a,long long b)
{
    if(b==0)
        return a;
    return gcd(b,a%b);
}
int main()
{
    cin>>a>>b;
    for(i=b;i>=a;i--)
    {
        for(j=a;j<min(i-maxdistance+1,i)&&i-j+1>maxdistance;j++)
        {
            if(gcd(i,j)==1)
            {
                maxdistance=i-j+1;j=i;
            }
        }
    }
    cout<<maxdistance;
    return 0;
}
