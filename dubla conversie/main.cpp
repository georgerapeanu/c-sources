#include <fstream>
using namespace std;
ifstream f("dconv.in");
ofstream g("dconv.out");
int v[20000],c[20000],cat[20000];
long long n;
int fitoa(unsigned long long n1)
{
    bool r;
    unsigned long long j,i=0,hold;
     while(n1!=0)
     {
         r=n1%2;
         n1=n1/2;
         v[++i]=r;
     }
     for(j=1;j<=i/2;j++)
     {
         hold=v[j];
         v[j]=v[i-j+1];
         v[i-j+1]=hold;
     }
     return i;
}
int fitoa2(unsigned long long int i)
{
  bool r=0;
  int n1,ca,j=1;
  n1=v[1]*10+v[2];
  cat[j]=n1/2;
  r=n1%2;
}
int main()
{
    unsigned long long int i;
    f>>n;
   i=fitoa(n);
   i=fitoa2(i);
   for(int j=1;j<=i;j++)
    g<<v[j];
    f.close();g.close();
    return 0;
}
