#include<fstream>
#include<iostream>
using namespace std;
ifstream f("vanatoare.in");
ofstream g("vanatoare.out");
unsigned long long rest,a,n,r,b=1,c=0,hold,gasit,s;
int main()
{
    f>>a>>n;
  while(gasit!=1)
  {
      s=b+c;
      r++;
      rest=s%2;
      s=s/2;
      if(rest==0)
      {
      if(a<s||n<s)
      {
          gasit=1;
          r--;
      }
      else
      {
          a-=s;
          n-=s;
      }
      }
      else
      {
      if(a<=s||n<s)
      {
          r--;
          gasit=1;
      }
      else
      {
          a-=s+1;
          n-=s;
      }
      }
      hold=b;
      b=b+c;
      c=hold;
  }
  g<<r<<"\n"<<a<<"\n"<<n;
  f.close();g.close();
  return 0;
}
