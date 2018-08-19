#include<fstream>
using namespace std;
ifstream f("triplu.in");
ofstream g("triplu.out");
int a,b,ca=1,cb=1,c,d,e,r,t;
int main()
{
   f>>a>>b;
   e=a;
   r=b;
   while(e!=0)
   {
       ca*=10;
       e=e/10;
   }
      while(r!=0)
   {
       cb*=10;
       r=r/10;
   }
   c=a*cb+b;
   d=b*ca+a;
   if(c>d)
    t=c*3;
   else
    t=d*3;
   g<<t;
   f.close();g.close();
   return 0;
}
