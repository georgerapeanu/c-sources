#include<fstream>
using namespace std;
ifstream f("vampiri.in");
ofstream g("vampiri.out");
int main()
{
    int z=0-1,y,d=0,m,v=0,x;
    char D;
    f>>m;
   while(v<m)
   {
       f>>D;
       f>>x;
       if (D=='D') d=d+x;
       else d=d-x;
       v++;
   }
   if(d<0)
    g<<"S"<<d*-1;
   else if(d==0)
    g<<0;
   else
    g<<"D"<<d;
    f.close();g.close();
    return 0;
}

