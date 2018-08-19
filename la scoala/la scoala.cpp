#include<iostream>
using namespace std;
int main()
{
    int n,k,p,i,d,l,j=1;
    cout<<"introduceti numarul de elevi din scoala:";
    cin>>n;
    for(i=n;i>=1;i--)
    {
        p=i*i;
        l=i;
        if(p<n)
        {
            i=0;
        }
    }
            d=n-p;
     cout<<"numar de elevi premiati:"<<d<<"\n";
     cout<<"elevii nepremiati:"<<"\n";
    for(k=p;k>=1;k--)
    {
        if(j%l==0)
        {
         if(k<=9)
         cout<<" "<<k<<" \n";
        else
            cout<<k<<"\n";
           j=1;
        }
        else
        {
        if(k<=9)
         cout<<" "<<k<<" ";
        else
            cout<<k<<" ";
         j++;
        }
    }
    return 0;
}
