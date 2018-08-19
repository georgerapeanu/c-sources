#include<iostream>
#include<fstream>
using namespace std;
ifstream f("inimi.in");
ofstream g("inimi.out");
int main()
{
    int v[10000],i,t,j,k[100000],n[100000],maxi=0,d[10000],l[10000],a[10000],maxiv=0,s;
    f>>t;
    for(j=1;j<=t;j++)
    {
    for(i=0;i<=3;i++)
    {
       f>>v[i];

    }
    for(i=0;i<=3;i++)
    {
        if(i==3)
            k[i]=v[i]*10+v[0];
            else
            k[i]=v[i]*10+v[i+1];
        n[i]=k[i];
    }
    for(i=0;i<=3;i++)
    {
        n[i+4]=k[i]/10+k[i]%10*10;
    }
    for(i=0;i<=7;i++)
    {
        if(n[i]>maxi)
        {
            maxi=n[i];
        }
    }
    }
    cout<<maxi;
      //aici e prima parte
      for(j=1;j<=t;j++)
    {
    for(i=0;i<=3;i++)
    {
       f>>d[i];

    }
    for(i=0;i<=3;i++)
    {
        if(i==3)
            l[i]=d[i]*10+d[0];
            else
            l[i]=d[i]*10+d[i+1];
        a[i]=l[i];
    }
    for(i=0;i<=3;i++)
    {
        a[i+4]=l[i]/10+l[i]%10*10;
    }
    for(i=0;i<=7;i++)
    {
        if(a[i]>maxiv)
        {
            maxiv=a[i];
        }
    }
    }
    if(maxi>=maxiv)
        s=maxi*100+maxiv;
    else
        s=maxiv*100+maxi;
    g<<s;
    f.close();
    g.close();
    return 0;
}
