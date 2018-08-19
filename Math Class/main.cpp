#include <iostream>
#include <iomanip>
#define EPS 1e-6L
using namespace std;
int N;
long double X[1005];
long double Y[1005];
long double st,dr;
long double dist(long double a,long double b)
{
    long double rez=0;
    for(int i=1;i<=N;i++)
        rez+=(a*X[i]+b-Y[i])*(a*X[i]+b-Y[i]);
    return rez;
}
long double check(long double a)
{
    long double st=-1000000.0L;
    long double dr=1000000.0L;
    while(dr-st>EPS)
    {
        long double m1=st+(dr-st)/3;
        long double m2=dr-(dr-st)/3;
        if(dist(a,m1)<dist(a,m2))
            dr=m2;
        else
            st=m1;
    }
    return dist(a,st);
}
int main()
{
    st=-1000000.0L;
    dr=1000000.0L;
    cin>>N;
    for(int i=1;i<=N;i++)cin>>X[i]>>Y[i];
    while(dr-st>EPS)
    {
        long double m1=st+(dr-st)/3;
        long double m2=dr-(dr-st)/3;
        if(check(m1)<check(m2))
            dr=m2;
        else
            st=m1;
    }
    cout<<fixed<<setprecision(6)<<check(st);
    return 0;
}
