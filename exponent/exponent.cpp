#include<fstream>
using namespace std;
ifstream f("exponent.in");
ofstream g("exponent.out");
int main()
{
    int i,n,k,j=0,l;
    f>>n>>k;
    for(i=1;i<=n;i++)
    {
        l=i;
       while(l%k==0)
           {
               l=l/k;
               j++;
           }
    }
    g<<j;
    f.close();g.close();
    return 0;
}
