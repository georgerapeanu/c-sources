#include <fstream>
using namespace std;
ifstream f("decodificare.in");
ofstream g("decodificare.out");
char c;
int main()
{
     do
     {
         c=f.get();
        if(c=='4')
        g<<'a';
        else if(c=='3')
        g<<'e';
        else if(c=='1')
        g<<'i';
        else if(c=='(')
        {g<<'o';c=f.get();}
        else if(c=='|')
        {
            c=f.get();
            if(c=='_')
            {
                c=f.get();g<<'u';
            }
            else
            g<<'d';
        }
        else if(c==92)
        {
            c=f.get();c=f.get();c=f.get();
            g<<'w';
        }
        else if(c=='7')
        g<<'t';
        else if(c=='$')
        g<<'s';
        else g<<c;
     }
     while(c!='\n');
     f.close();g.close();
    return 0;
}

