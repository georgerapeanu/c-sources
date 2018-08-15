#include<fstream>
#include<iostream>
using namespace std;
ifstream f("culori.in");
ofstream g("culori.out");
int main()
{
    int n,k;
    f>>n>>k;
    int i,v[n];
    for(i=0;i<n;i++)
    {
        f>>v[i];
    }
    int y=0;
    for(i=0;i<n;i++)
    {
        if(i==0)
        {
            if(v[n-1]==v[0]&&v[0]==v[n])
                y++;
        }
        else if(i==n-1)
        {
            if(v[n-2]==v[n-1]&&v[n-1]==v[0])
                y++;
        }
        else
        {
            if(v[i-1]==v[i]&&v[i]==v[i+1])
                y++;
        }
    }
    g<<y<<"\n";
    int d[n+k-1],j,maxim=0,w=0,l;
    for(i=0;i<n;i++)
    {
        d[i]=v[i];
    }
    for(i=n;i<n+k-1;i++)
    {
        d[i]=v[i-n];
    }
    for(i=0;i<n;i++)
    {
        for(j=i;j<i+k;j++)
        {
            w=1;
              for(l=i;l<i+k&&l!=j;l++)
              {
                  if(d[l]==d[j])
                    w++;
              }
              if(w>maxim)
                maxim=w;
        }
    }
    g<<maxim;
    f.close();g.close();
    return 0;
}
