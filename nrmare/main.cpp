#include <fstream>
using namespace std;
ifstream f("nrmare.in");
ofstream g("nrmare.out");
int i,n,k,j;
char c[200],l;
int main()
{
    f>>n>>k;l=f.get();
    f.getline(c,200);
    i=0;
   for(i=0;i<n-1&&k!=0;i++)
   {
       if(c[i]<c[i+1])
       {
           for(j=i;j<n-1;j++)
           c[j]=c[j+1];
           n--;
           k--;
           c[n]=0;
       }
   }
   if(k!=0)
   for(i=n-k;i<n;i++)
   c[i]=0;
   g<<c;
    f.close();g.close();
    return 0;
}
//neterminat
