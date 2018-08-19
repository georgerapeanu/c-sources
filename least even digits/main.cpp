#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
long long maxB,minA;
long long X;
int even(long long nr)
{
    if(nr<0)nr=-nr;
    int rez=(nr==0);
    while(nr)
    {
        rez+=((nr%10)%2==0);
        nr/=10;
    }
    return rez;
}
void checkparticular()
{
    long long cX=X;
    int nrcf=(X==0);
    while(cX)
    {
        cX/=10;
        nrcf++;
    }
    if(nrcf>1&&even(X)==1&&(long long)(X/pow(10,nrcf-1))%2==0)
    {
        int pcif=X/pow(10,nrcf-1);
        long long dist=(pcif+1)*pow(10,nrcf-1)+(pow(10,nrcf-1)-1)/9;
        dist=dist-X;
        cout<<dist*dist;exit(0);
    }
}
long long times=0;
int main() {
    cin>>X;
    maxB=minA=X;
    if(even(X)==0){cout<<-1;return 0;}
    checkparticular();
    while(even(X)<=even(minA-1))
    {
        minA--;
        times++;
        //if(times>15000000){cout<<-1;return 0;}
    }
    times=0;
    while(even(X)<=even(maxB+1))
    {
        maxB++;
        times++;
        //if(times>15000000){cout<<-1;return 0;}
    }
    cout<<(maxB-X+1)*(X-minA+1);
    return 0;
}
