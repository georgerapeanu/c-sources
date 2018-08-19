#include <fstream>
using namespace std;
ifstream f("fib.in");
ofstream g("fib.out");
unsigned long long fib[10001]={2,1,2},a,b;
bool nr0;
short n,i,j,nr;
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>nr;a=0;b=0;
       if(nr>fib[0])
           {
               while(fib[0]<nr)
               {
                   fib[++fib[0]]=fib[fib[0]-1]+fib[fib[0]-2];
               }
           }
        for(j=1;j<=nr;j++)
        {
           f>>nr0;
           if(nr0==1)
           {
                a+=fib[nr-j+1];
           }
        }
        f>>nr;
       if(nr>fib[0])
           {
               while(fib[0]<nr)
               {
                   fib[++fib[0]]=fib[fib[0]-1]+fib[fib[0]-2];
               }
           }
        for(j=1;j<=nr;j++)
        {
           f>>nr0;
           if(nr0==1)
           {
                b+=fib[nr-j+1];
           }
        }
        if(a==b)
        g<<"DA"<<"\n";
        else
        g<<"NU"<<"\n";
    }
    f.close();g.close();
    return 0;
}
