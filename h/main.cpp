#include <fstream>
using namespace std;
ifstream f("h.in");
ofstream g("h.out");
long long n,i,s,s1,k;
int main()
{
    f>>n;
    s=n*(4*n+1);
   while(s1!=s)
   {
       if(((s-s1)-(4*n)+k)>=0)
       {
           s1+=4*n;
           s1-=k;
           g<<((4*n)-k)<<" ";
       }
       else
       {
           g<<(s-s1);
           s1=s1+(s-s1);
       }
       k++;
   }
   f.close();g.close();
    return 0;
}
