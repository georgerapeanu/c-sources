#include <iostream>
using namespace std;
int cost[10]={6,2,5,5,4,5,6,3,7,6};
int a,b,i,ci;
long long rez;
int main()
{
    cin>>a>>b;
    for(i=a;i<=b;i++)
    {
        ci=i;
        while(ci)
        {
            rez+=cost[ci%10];
            ci/=10;
        }
    }
    cout<<rez;
    return 0;
}
