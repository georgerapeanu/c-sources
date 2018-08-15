#include<iostream>
using namespace std;
int main()
{
    long d,n,uc,k=18,i,j,h=0,l,g=1;
    cout<<" ";
    cin>>n;
    l=n;
    while(l>9)
    {
        g=g*10;
        l=l/10;
    }
    while(n!=0)
    {
        k=18;
        uc=n/g;
        n=n%g;
        g=g/10;
        if(uc%2==1)
        {
            h=1;
            for(i=1;i<=uc;i+=2)
            {
                k=k-2;
                for(j=k;j>=0;j--)
                {
                   cout<<" ";
                }
                for(j=1;j<=i;j++)
                {
                    cout<<uc<<" ";
                }
                cout<<"\n";
            }
            for(i=uc-2;i>=1;i=i-2)
            {
                k=k+2;
                for(j=k;j>=0;j--)
                {
                    cout<<" ";
                }
                for(j=1;j<=i;j++)
                {
                    cout<<uc<<" ";
                }
                cout<<"\n";
            }
        }
        if(h==0)
        {
            h=0;
        }
    }
    if(h==0)
        cout<<"cufarul nu se deschide";
    return 0;
}
