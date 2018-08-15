#include<fstream>
#include<iostream>
using namespace std;
ifstream f("numerus.in");
ofstream g("numerus.out");
int main()
{
    int l,j,k,n,m,i=0,o;
    f>>k;
    f>>n;
    if(k%2==0)
    {
       m=k*5;
       g<<m<<" ";
       i=0;
       while(i<=4)
       {
       g<<m<<" ";
       m--;
       i++;
       }
    }
    else
    {
        m=k*5;
        m=m-4;
        g<<m<<" ";
        i=0;
        while(i<=3)
        {
            m++;
            i++;
            g<<m<<" ";
        }
        g<<m<<" ";
    }
    if(n%5==0)
        l=n/5;
    else
        l=n/5+1;
        g<<"\n"<<l<<"\n";
    if(n%5==0)
    {
        if(n%2==0)
     g<<"A"<<" "<<"B"<<"\n";
        else
            g<<"E"<<" "<<"F"<<"\n";
    }
    else
    {
        j=l*5;
        if(l%2==0)
        {
          o=2+(j-n);
        }
        else
            o=n-(j-4)+1;
    }
    switch(o)
           {
             case 1:g<<"A ";
             break;
             case 2:g<<"B ";
             break;
             case 3:g<<"C ";
             break;
             case 4:g<<"D ";
             break;
             case 5:g<<"E ";
             break;
             case 6:g<<"F ";
             break;
           }
    f.close();g.close();
    return 0;
}
