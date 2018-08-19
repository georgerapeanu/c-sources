#include <iostream>
using namespace std;
long long f(long long a,long long b)
{
    if(!b)return 0;
    long long d=1,mindist=1LL<<52;
    bool prime=1;
    for(long long i=2;i*i<=a;i++)
    {
        if(a%i==0)
        {
            prime=0;
            if(mindist>b%i||(mindist==b%i&&d<i))
            {
                mindist=b%i;
                d=i;
            }
            if(mindist>b%(a/i)||(mindist==b%(a/i)&&d<(a/i)))
            {
                mindist=b%(a/i);
                d=(a/i);
            }
        }
    }
    if(mindist>b%a||(mindist==b%a&&d<a))
    {
        mindist=b%a;
        d=a;
    }
    if(prime)
    {
        if(a>b)return b;
        return b%a+b/a;
    }
    return mindist+f(a/d,(b-mindist)/d);
}
int main()
{
    long long a,b;
    cin>>a>>b;
    cout<<f(a,b)<<"\n";
    return 0;
}
