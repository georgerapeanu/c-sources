#include<fstream>
using namespace std;
ifstream f("xyz.in");
ofstream g("xyz.out");
int main()
{
    int x,y,z,i;
    f>>x>>y>>z;
    g<<y;
    for(i=1;i<x;i++)
    {
        g<<z;
    }
    g.close();f.close();
    return 0;
}
