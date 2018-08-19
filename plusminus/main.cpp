#include <fstream>
using namespace std;
ifstream f("plusminus.in");
ofstream g("plusminus.out");
short sens=1;
char c;
long long rez,nr;
int main()
{
    while(f>>nr>>c)
    {
        rez+=nr*sens;
        if(c=='+')
            sens=1;
        else if(c=='-')
            sens=-1;
    }
    rez+=sens*nr;
    g<<rez;
    f.close();
    g.close();
    return 0;
}
