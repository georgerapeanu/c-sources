#include <cstdio>
#include <iostream>
#include <cmath>
#define PI 3.14159265359
using namespace std;
double P,x,y;
int N;
int dist(int x,int y)
{
    return x*x+y*y;
}
double dtor(double deg)
{
    return (deg*PI)/180;
}
int main()
{
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>P>>x>>y;
        x-=50;y-=50;
        double unghi=-atan2(-x,y);
        if(unghi<0)
            unghi=2*PI+unghi;
        if(dist(x,y)<=2500&&dtor((360*P)/100)>=unghi)
            cout<<"Case #"<<i<<": black\n";
        else
            cout<<"Case #"<<i<<": white\n";
    }
    return 0;
}
