#include<iostream>
using namespace std;
int main()
{
    long d,i,j,n,k,l=0,s=0,g;
    int p[10000];
    cout<<" ";
    cin>>n>>k;
    for(j=2;j<=n;j++)
    {
    for(i=1;i<=j/2;i++)
    {

         if(i==j)
        {
            g=1;
        }
        else if(i==1)
            g=1;
        else
        {
        if(j%i==0)
        {
            g=0;
            i=j/2+1;
        }
        else
            g=1;
        }
    }
    if(g==1)
    {
        p[s]=j;
        l++;
        s++;
    }
    }
    if(l%2==0)
    {
        if(2*k>=l)
        {
            for(i=0;i<=l-1;i++)
            {
                cout<<p[i]<<" ";
            }
        }
        else
        {
            d=(l-2*k)/2;
            for(i=d;i<l-d;i++)
            {
                cout<<p[i]<<" ";
            }
        }
    }
    else
        {
            if(2*k-1>=l)
            {
                for(i=0;i<=l-1;i++)
            {
                cout<<p[i]<<" ";
            }
            }
            else
                {
                    d=(l-(2*k-1))/2;
                    for(i=d;i<l-d;i++)
                    {
                        cout<<p[i]<<" ";
                    }
                }
        }
        return 0;
}
