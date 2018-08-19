#include <fstream>
#include <iostream>
using namespace std;
ifstream f("numar2.in");
ofstream g("numar2.out");
long long v[50],y[50],z[10],uc,i,n,j,l,b,cx,x,nr;
int main()
{
    f>>n;
    for(i=0;i<n;i++)
    {
        f>>v[i];
    }
    j=0;
   for(i=0;i<n;i++)
    {
       y[j]=v[i];
       while(v[i]<v[i+1])
       {
           y[j]+=v[i+1];
           i++;
       }
       j++;
    }
    for(i=0;i<j;i++)
    {
        x=y[i];
        do
        {
            cx=0;
            while(x!=0)
            {
                uc=x%10;
                x=x/10;
                cx+=uc;
            }
            x=cx;
        }
        while(x>9);
        z[x]=1;
    }
    for(i=9;i>=0;i--)
   {if(z[i]!=1)
    nr=nr*10+i;}
    g<<nr;
    f.close();g.close();
    return 0;
}
