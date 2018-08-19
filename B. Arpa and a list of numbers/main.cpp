#include <iostream>
using namespace std;
long long sum[2000005];
int cnt[2000005];
int N,a,x,y;
long long cost;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N>>x>>y;
    for(int i=1;i<=N;i++)
    {
        cin>>a;
        sum[a]+=a;
        cnt[a]++;
    }
    for(int i=1;i<=2000000;i++)
    {
        sum[i]+=sum[i-1];
        cnt[i]+=cnt[i-1];
    }
    cost=1LL<<60;
    for(int i=2;i<=2000000;i++)
    {
        long long a=0,b=0;
        for(int j=i;j<=2000000;j+=i)
        {
            if(i-1<=x/y)
            {
                b+=1LL*(cnt[j]-cnt[j-i])*j-(sum[j]-sum[j-i]);
            }
            else
            {
                a+=cnt[j-x/y-1]-cnt[j-i];
                b+=1LL*(cnt[j]-cnt[j-x/y-1])*j-(sum[j]-sum[j-x/y-1]);
            }
        }
       // if(i==17)cout<<a<<" "<<b<<"\n\n\n\n";
        cost=min(cost,1LL*a*x+1LL*b*y);
    }
    cout<<cost;
    return 0;
}
