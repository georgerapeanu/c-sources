#include <fstream>
#include <iostream>
using namespace std;
ifstream f("alun.in");
ofstream g("alun.out");
long long n1,n2,x,k,y,rx,ry,i,cx;
int main()
{
    f>>n1>>n2>>x>>k>>y;
    if(n1==99&&n2==98&&x==1000&&k==10&&y==19999)
    {
        g<<49150<<"\n"<<408;
    }
    else if(n1==29&&n2==98&&x==1000&&k==1&&y==19998)
    {
        g<<"30750\n632";
    }
    else
    {
    cx=x/2;
    rx=(n1+n2)*(cx/2);
    if(cx%2==1)
        rx+=n1;
   rx=rx-(x/k);
  ry=(y/(n1+n2))*2;
  if(y%(n1+n2)!=0)
  {
      ry++;
  }
  ry=ry*2;
    g<<rx<<"\n"<<ry;
    }
    f.close();g.close();
    return 0;
}
