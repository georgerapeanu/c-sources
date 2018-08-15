#include <iostream>
using namespace std;
int val[]={1,2,4,8};
int cost[4];
long long N;
int main()
{
    for(int i=0;i<4;i++)cin>>cost[i];
    cin>>N;N*=4;
    for(int i=0;i<4;i++)
    {
        for(int j=i+1;j<4;j++)
        {
            cost[j]=min(0LL+cost[j],1LL*cost[i]*val[j]/val[i]);
        }
    }
    long long rez=0;
    for(int i=3;i>=0;i--)
    {
        rez+=(N/val[i])*cost[i];
        N%=val[i];
    }
    cout<<rez;
    return 0;
}
