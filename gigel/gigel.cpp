#include<iostream>
using namespace std;
int main()
{
    long long n,l,a,z,c,i=0,j=0,r,v[12]={31,61,91,122,150,181,212,242,273,303,334,365},m;
    cout<<"n=";
    cin>>n;
    n=n/86400;
    if(n>=837)
    {
        n=n-(n-837)/(4*365+1)-1;
    }
    c=n/365;
    r=n%365;
    j=0;
    for(i=0;i<12;i++)
    {
        if(v[i]<r)
        {
            j=i+1;
        }
    }
    if(j!=0)
    {
        z=r-v[j-1];
    }
    else
        z=r;
    cout<<"gigel are:"<<c<<" ani "<<j<<" luni "<<z<<" zile";
    return 0;
}
