#include <iostream>
#include <iomanip>
#include <algorithm>
#define x first
#define y second
using namespace std;
int st,dr;
int N;
pair<int,int> V[60005];
double gtime(double x)
{
    double rez=0;
    for(int i=1;i<=N;i++)
        rez=max(rez,fabs(V[i].x-x)*1.0/V[i].y);
    return rez;
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++) cin>>V[i].x;
    for(int i=1;i<=N;i++) cin>>V[i].y;
    double st=1,dr=1000000000;
    int i=1;
    while(i<=150)
    {
        double l,r;
        l=st+(dr-st)/3;
        r=dr-(dr-st)/3;
        if(gtime(l)<gtime(r))
            dr=r;
        else
            st=l;
        i++;
    }
    cout<<fixed<<setprecision(7)<<gtime(st);
    return 0;
}
