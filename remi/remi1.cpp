#include<iostream>
#include<fstream>
using namespace std;
ifstream f("remi1.in");
ofstream g("remi1.out");
int main()
{
    int mini,j,n,maxim=0,l=0,i;
    f>>j>>n;
    int v[n],o[n+1];
    for(i=0;i<n;i++)
    {
        f>>v[i];
    }
    mini=v[0];
    for(i=0;i<n;i++)
    {
        if(v[i]>maxim)
        {
            maxim=v[i];
            l=i;
        }
        if(mini>v[i])
            mini=v[i];
    }
int b,m,hold;
    b=v[l]*10+v[0];
    m=v[1]*10+v[2];
    if(b<m)
    {
        hold=v[0];
        for(i=0;i<n-1;i++)
            v[i]=v[i+1];
        v[n-1]=hold;
    }
    else
        {
            hold=v[l];
            for(i=l;i>0;i--)
            {
                v[i]=v[i-1];
            }
            v[0]=hold;
        }
        i=0;
    while(v[i]>j)
    {
        i++;
    }
    if(j>mini)
    {
    hold=v[n-1];
    for(l=n-1;l>i;l--)
    {
        v[l]=v[l-1];
    }
    v[i]=j;
    for(i=0;i<n;i++)
    {
        o[i]=v[i];
    }
    o[n]=hold;
        for(i=0;i<=n;i++)
       g<<o[i];
    }
    else
    {
        for(i=0;i<n;i++)
        {
        g<<v[i];
        }
        g<<j;
}
    f.close();g.close();
    return 0;
}
