#include <fstream>
using namespace std;
ifstream f("chipsidale.in");
ofstream g("chipsidale.out");
long long i,chip,nrc,dale,n,v[1000];
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>v[i];
    }
    while(n>2)
   {
       for(i=1;i<=n/2;i++)
       {
           v[i]=v[i]+v[n-i+1];
       }
       nrc++;
       if(n%2==0)
       {
           chip+=v[n/2];
           v[n/2]=0;
           n=n/2-1;
       }
       else
       {
           chip+=v[n/2+1];
           v[n/2+1]=0;
           n=n/2;
       }
   }
   for(i=1;i<=n;i++)
   {
       dale+=v[i];
   }
   g<<nrc<<" "<<chip<<"\n"<<n<<" "<<dale;
   f.close();g.close();
    return 0;
}
