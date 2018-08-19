#include<fstream>
#include<iostream>
#include<algorithm>
using namespace std;
ifstream f("cluburi.in");
ofstream g("cluburi.out");
int main()
{
    int n,d,c,club=1,k=0,l;
    f>>n;
    c=n;
    d=n;
  while(d)
  {

      if(d%2==1)
      {
        k++;
      }
      d=d/2;
  }
  g<<k<<"\n";
  while(c)
  {
    if(c%2==0)
        {club=club*2;}
    else
    {
        g<<club<<" ";
        club=club*2;
    }
        c=c/2;
  }
    return 0;
}
