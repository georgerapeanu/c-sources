#include <iostream>
using namespace std;
long long t,w,b,cmmmc,nr;
void euclid(long long a,long long int b, long long int *d)
{
    if (b == 0) {
        *d = a;
    } else
        euclid(b, a % b, d);
}
int main()
{
    cin>>t>>w>>b;
    euclid(w,b,&cmmmc);
    cmmmc=(w/cmmmc)*b;
    nr+=t/cmmmc*2+1;
    if(t%cmmmc==0)
    nr--;
    if(w==1)
    nr=t/b;
    if(b==1)
    nr=t/w;
    cmmmc=0;
    euclid(nr,t,&cmmmc);
    cout<<nr/cmmmc<<"/"<<t/cmmmc;
    return 0;
}
