#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
long double alfa;
long double PI=3.14159265358979323846;
long double fangle=1.0f*60/180*PI;
int N;
long double X[100];
long double Y[100];
long double x,y;
long double dist(int i,int j)
{
    return sqrt(pow(X[i]-X[j],2)+pow(Y[i]-Y[j],2));
}
int main() {
    cin>>N;
    alfa=fangle/(N-2);
    cout<<"0 0\n";
    x=0;y=1;
    X[1]=0;Y[1]=0;
    for(int i=2;i<=N;i++)
    {
        cout<<fixed<<setprecision(12)<<x<<" "<<y<<"\n";
        X[i]=x;Y[i]=y;
        long double nx,ny;
        nx=x*cos(alfa)-y*sin(alfa);
        ny=x*sin(alfa)+y*cos(alfa);
        x=nx;
        y=ny;
    }
    for(int i=1;i<=N;i++)
        for(int j=i+1;j<=N;j++)
            cout<<fixed<<setprecision(12)<<i<<" "<<j<<" "<<dist(i,j)<<"\n";
    return 0;
}
