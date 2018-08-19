#include <iostream>
#define EPS 0.00001
#define inf 4e10L
using namespace std;
long double st,dr;
int N;
int P;
int a[100005];
int b[100005];
bool ok(long double t)
{
    long double charge=t;
    for(int i=1;i<=N;i++)
    {
        if(t*a[i]>b[i])charge-=(t*a[i]-b[i])/(long double)P;
    }
    return (charge>=0.0L);
}
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N>>P;
    for(int i=1;i<=N;i++)cin>>a[i]>>b[i];
    st=0;
    dr=inf+2.0L;
    while(dr-st>EPS)
    {
        long double mid=(st+dr)/2;
        if(ok(mid))
            st=mid;
        else
            dr=mid;
    }
    if(dr>inf)
        cout<<-1;
    else
        cout<<dr;
    return 0;
}
