#include <iostream>
#include <iomanip >
using namespace std;
long double N;
int M;
long double p;
int main()
{
    cin>>N>>M;
    for(int i=1;i<=M;i++)p+=(N-p)/N;
    cout<<fixed<<setprecision(12)<<p;
    return 0;
}
