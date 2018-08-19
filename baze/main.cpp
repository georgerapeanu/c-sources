#include <fstream>
using namespace std;
ifstream f("baze.in");
ofstream g("baze.out");
int itoa(unsigned long long nr,short baza)
{
    int j=0,i=0;
    char vec[10]={0,0,0,0,0,0,0,0,0,0};
      while(nr!=0)
      {
          vec[i++]=nr%baza;
          nr/=baza;
      }
      for(j=1;j<i;j++)
      {
          if(vec[j]!=vec[0])
          return 0;
      }
      return 1;
}
int main()
{
    short n=0,i=0,baza;
    unsigned long long k;
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>k;
        baza=2;
        while(itoa(k,baza)==0)
        baza++;
        g<<baza<<" ";
    }
    f.close();g.close();
    return 0;
}
