#include<iostream>
using namespace std;
int main()
{
    long n,a,b,maxi=0,i=1,m,j=1,k=1,d;
    cout<<" ";
    cin>>n;
    m=n;
    while(m>=9)
    {
        m=m/10;
        j++;
        i=i*10;
    }
    for(k=1;k<=j;k++)
    {
        d=(n/i)*(n%i);
        if(maxi<d)
        {
            a=n/i;
            b=n%i;
            maxi=d;
        }
        i=i/10;
    }
    cout<<a<<"\n"<<b<<"\n"<<maxi;
    return 0;
}
