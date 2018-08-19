#include<fstream>
#include<iostream>
using namespace std;
ifstream f("vopsea.in");
ofstream g("vopsea.out");
int main()
{
    int n,p,l,o;
    f>>n>>p;
    l=n-p;
    g<<l<<endl;
    o=n/p;
    g<<o;
    f.close();g.close();
    return 0;
}
