#include <iostream>
#include <cmath>
using namespace std;
long double a,unghi,N;
long double PI;
int x=1;
int main()
{
    PI=acos(-1);
    cin>>N>>a;
    unghi=PI/N;
    a=a*PI/180;
    for(int i=1;i<=N-2;i++)
    {
        if(abs(a-unghi*i)<abs(a-unghi*x))
            x=i;
    }
    cout<<"1 2 "<<N-x+1;
    return 0;
}
