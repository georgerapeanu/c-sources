#include <fstream>
using namespace std;
ifstream f("galbeni.in");
ofstream g("galbeni.out");
long long int n,s,k,i=1,cs,pk=1,cfn[11],uc,j,l;
int main()
{
    f>>s>>k>>n;
   i=0;
   while(i!=k)
   {
       pk=pk*10;
       i++;
   }
   i=1;
   while(i!=n)
   {
       cs=s;l=1;
       while(cs!=0)
       {
           uc=cs%10;
           cs=cs/10;
           cfn[l]=uc;l++;
       }
       for(j=1;j<=k;j++)
       {
           if(cfn[j]!=0)
           {
           s=s*cfn[j];
           }
       }
       s=s*8;s=int(s/9);
       if(s>=pk)
        s=s%pk;
       else
       {
           while(s<pk/10)
           {
               s=s*10+9;
           }
       }
       i++;
   }
   g<<s;
   f.close();g.close();
    return 0;
}
