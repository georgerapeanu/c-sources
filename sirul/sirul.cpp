#include<fstream>
#include<cstring>
using namespace std;
ifstream f("sirul.in");
ofstream g("sirul.out");
int n,i;
char a[6765],b[6765],hold[6765];
int main()
{
    f>>n;
        if(n<=2)
       {
           if(n==1)   g<<"a";
           if(n==2)   g<<"b";
       }
       else{
   for(i=1;i<=n;i++)
   {
       if(i<=2)
       {
           if(i==1)   a[0]='a';
           if(i==2)   b[0]='b';
       }
       else
       {
           strcpy(hold,b);
           strcat(b,a);
           strcpy(a,hold);
       }
   }
   for(i=0;i<strlen(b);i++)
    g<<b[i];
    }
   f.close();g.close();
   return 0;
}
