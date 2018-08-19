#include <fstream>
using namespace std;
ifstream f("alice.in");
ofstream g("alice.out");
long long v[28],j,i,t,a,b,n;
int main()
{
    f>>t;
    for(i=1;i<=t;i++)
    {
        n=0;
        f>>a;
        for(j=2;j<=a;j++)
        {
            b=j;
            while(b<=a)
            {
                v[b]++;
                b=b+j;
            }
       }
               for(j=1;j<=a;j++)
        {
        if(v[j]%2==1)
        {n++;}
        v[j]=0;
        }
        g<<n<<"\n";
    }
        f.close();g.close();
    return 0;
}
