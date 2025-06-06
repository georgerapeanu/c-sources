#include <iostream>
#include <cmath>
#define ll long long
using namespace std;
ll n,x[100001],y[100001],nrpos,punct;
double lungime(ll x1,ll y1,ll x2,ll y2)
{
    return sqrt(pow((x1-x2),2)+pow((y1-y2),2));
}
double area(double a,double b,double c)
{
    double s;
    s=(a+b+c)/2;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}
ll gcd(ll a,ll b)
{
    if(b==0)
    return a;
    if(a==0)
    return b;
    ll r=a%b;
    while(r!=0)
    {
        a=b;
        b=r;
        r=a%b;
    }
    return b;
}
ll abs1(ll a)
{
    if(a<0)
    a*=-1;
    return a;
}
ll pct(ll x1,ll y1,ll x2,ll y2)
{
    return (gcd(abs1(x1-x2),abs1(y1-y2)));
}

int ceil0(double x)
{
    if(x>=int(x)+0.5)
    return int(x+1);
    return int(x);
}
void calcul(ll nrp,ll selct[])
{
    nrpos++;
    ll punctx,puncty;
    punctx=x[selct[1]];
    puncty=y[selct[1]];
    double arie=0;
    double a=0,b=0,c=0;
    ll pt=0;
    for(ll i=2;i<nrp;i++)
    {
//        if(i==nrp)
//        {
//            a=lungime(x[selct[1]],y[selct[1]],x[selct[nrp]],y[selct[nrp]]);
//            b=lungime(punctx,puncty,x[selct[1]],y[selct[1]]);
//            c=lungime(punctx,puncty,x[selct[nrp]],y[selct[nrp]]);
//            arie+=area(a,b,c);
//            pt+=pct(x[selct[1]],y[selct[1]],x[selct[nrp]],y[selct[nrp]])+1;
//        }
//        else
//        {
            a=lungime(x[selct[i]],y[selct[i]],x[selct[i+1]],y[selct[i+1]]);
            b=lungime(punctx,puncty,x[selct[i+1]],y[selct[i+1]]);
            c=lungime(punctx,puncty,x[selct[i]],y[selct[i]]);
            arie+=area(a,b,c);
       // }
    }
    for(ll i=1;i<=nrp;i++)
    {
        if(i==nrp)
        pt+=pct(x[selct[1]],y[selct[1]],x[selct[i]],y[selct[i]])+1;
        else
        pt+=pct(x[selct[i]],y[selct[i]],x[selct[i+1]],y[selct[i+1]])+1;
    }
    pt-=nrp ;
    punct+=ceil0(arie)-(pt/2)+1;
}
void selectare(ll nr,ll nrp,bool slct[],ll selct[])
{
    if(nrp<nr)
    {
        int i;
        for(i=selct[nrp]+1;i<=n;i++)
        {
            if(slct[i]==0)
            {
                slct[i]=1;
                selct[nrp+1]=i;
                selectare(nr,nrp+1,slct,selct);
                slct[i]=0;
                selct[nrp+1]=0;
            }
        }
    }
    else
    calcul(nrp,selct);
}
int main()
{
    std::cin>>n;
    bool slct[100001]={false};
    ll selct[100001]={0};
    for(ll i=1;i<=n;i++)
    {
        std::cin>>x[i]>>y[i];
    }
    for(ll i=3;i<=n;i++)
    {
        selectare(i,0,slct,selct);
    }
    std::cout<<double(double(punct)/nrpos);
    return 0;
}
