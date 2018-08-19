#include<fstream>
#include<iostream>
using namespace std;
ifstream f("bancomat.in");
ofstream g("bancomat.out");
int s,n,a,i,c;
int main()
{
   f>>s>>n;
   for(i=1;i<=n;i++)
   {
       f>>a;
       c=a%10;
       a=a/10;
       if(c==2)
       {
           s=s+a;
       }
       else
       {
           if(s>=a)
           {
               s-=a;
           }
       }
   }
   g<<s;
   f.close();g.close();
   return 0;
}
