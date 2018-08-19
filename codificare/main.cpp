#include <fstream>
using namespace std;
ifstream f("codificare.in");
ofstream g("codificare.out");
char c;
int main()
{
    c=f.get();
    while(c!='\n')
    {
         if(c=='a'||c=='A')
         {
             g<<4;
         }
         else if(c=='e'||c=='E')
         {
               g<<3;
         }
        else if(c=='i'||c=='I')
        {
            g<<1;
        }
        else if(c=='o'||c=='O')
        {
            g<<"()";
        }
        else if(c=='u'||c=='U')
        {
          g<<"|_|";
        }
        else if(c=='t'||c=='T')
        {
           g<<"7";
        }
        else if(c=='d'||c=='D')
        {
            g<<"|)";
        }
        else if(c=='w'||c=='W')
        {
            g<<'134'<<"/"<<'134'<<"/"<<'134';
        }
        else if(c=='s'||c=='S')
        {
           g<<"$";
        }
        else
        {
             g<<c;
        }
        c=f.get();
    }
    return 0;
}
//A = 4
//E = 3
//I = 1
//O = ()
//U = |_|
//T = 7
//D = |)
//W = \/\/
//S = $
