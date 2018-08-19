#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;
long double h,n;
vector<long double> rez;
void solve(long double h,long double b,long double a,long double n,long double ctg,long double fh)
{
    if(!n)return ;
    long double bp=sqrt(b*b-a*4*ctg);
    long double hp=(b-bp)/(2*ctg);
    rez.push_back(h-hp);
    solve(h-hp,bp,a,n-1,ctg,fh);
}
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>n>>h;
    solve(h,1,h/(2*n),n-1,1/(2*h),h);
    for(int i=rez.size()-1;i>=0;i--)cout<<fixed<<setprecision(10)<<rez[i]<<" ";
    return 0;
}
