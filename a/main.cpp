#include <iostream>
using namespace std;
int n=999;
int main()
{
    int i;
   for(i=32;i>=1;i--)
   {
       if(n%i==0)
       {
           cout<<i<<" "<<(n/i)<<" ";
           break;
       }
   }
   int a=181,b=n/i,r;
   r=a%b;
   while(r!=0)
   {
       a=b;b=r;r=a%b;
   }
   cout<<b;
    return 0;
}
