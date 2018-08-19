#include<fstream>
using namespace std;
ifstream f("adunare.in");
ofstream g("adunare.out");
int main()
{
    unsigned long long a,b,s;
    f>>a>>b;
    s=a+b;
    g<<s;
    f.close();g.close();
    return  0;
}
