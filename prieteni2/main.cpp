#include <fstream>
using namespace std;
ifstream f("prieteni2.in");
ofstream g("prieteni2.out");
int n,s,nrmin=1001,t,i;
int main()
{
   f>>n;
   for(i=1;i<=n;i++)
   {
       f>>t;
       s=s+t;
       if(t<nrmin)
        nrmin=t;
   }
    s=s+nrmin*(n-3);
    g<<s;
    f.close();g.close();
    return 0;
}
