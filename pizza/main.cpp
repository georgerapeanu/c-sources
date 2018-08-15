#include <fstream>
#include <iostream>
using namespace std;
ifstream f("pizza.in");
ofstream g("pizza.out");
long n,i,a1,b1,s,nr_3sfert,nr_jum,nr_sfert;
char a,b,c;
int main()
{
    f>>n;
    for(i=0;i<n;i++)
    {
       f>>a>>b>>c;
       a1=a-'0';
       b1=c-'0';
      if(a1==3)
        nr_3sfert++;
      if(a1==1)
      {
          if(b1==2)
            nr_jum++;
          else
            nr_sfert++;
      }
    }
    nr_sfert-=nr_3sfert;
    if(nr_jum%2==1)
        nr_sfert-=2;
    if(nr_sfert<0)
        nr_sfert=0;
    s+=nr_3sfert+(nr_jum+1)/2+(nr_sfert+3)/4;
    g<<s;
   f.close();g.close();
    return 0;
}
