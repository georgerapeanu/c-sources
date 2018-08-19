#include <fstream>
#include <cstring>
using namespace std;
ifstream f("helper.in");
ofstream g("helper.out");
char v[100000];
int main()
{
    f>>v;
    g<<strlen(v);
    return 0;
}
