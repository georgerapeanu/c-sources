#include<fstream>
using namespace std;
ifstream f("capete.in");
ofstream g("capete.out");
int main()
{
    int c,z;
    f>>z;
    c=6+5*(z-1)-1;
    g<<c;
    f.close();g.close();
    return 0;
}
