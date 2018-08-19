#include <iostream>
using namespace std;
long long a,b,k,n,i,dim,nr,nr2;
int main()
{
    cin>>k>>a>>b;
    nr=a/k;
    while(nr*k<a)
    nr++;
    nr2=b/k;
    while(nr2*k>b)
    nr2--;
    dim=nr2-nr+1;
    cout<<dim;
    return 0;
}
