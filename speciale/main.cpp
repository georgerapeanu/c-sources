#include <fstream>
#include <iostream>
using namespace std;
ifstream f("speciale.in");
ofstream g("speciale.out");
long v1[10]={0,1,12,123,1234,12345,123456,1234567,12345678,123456789},v2[10]={0,9,98,987,9876,98765,987654,9876543,987654321};
int p,k;
long long n,a,b,i;
int cf[10],nrcf;
int main()
{
    f>>p>>k>>n>>a>>b;
    if(p==1)
    g<<v2[k];
    else if(p==2)
     {
        while(n!=0)
        {
            cf[n%10]++;
            nrcf++;
            n/=10;
        }
        for(i=1;i<=nrcf;i++)
     }
    else
   {
       int j=1,nr=0;
       while(v2[j]<a)
       j++;
       while((v2[j]>=a&&v2[j]<=b)||(v1[j]>=a&&v1[j]<=b))
       {
           if((v2[j]>=a&&v2[j]<=b))
           nr++;
           if((v1[j]>=a&&v1[j]<=b))
           nr++;
           j++;
       }
       g<<nr;
   }
    return 0;
}
