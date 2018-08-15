#include <fstream>
using namespace std;
ifstream f("cifre2.in");
ofstream g("cifre2.out");
int n;
int main()
{
    f>>n;
    if(n%2==0)
        g<<"6 234567890";
    else
        g<<"1 789012345";
        f.close();g.close();
    return 0;
}
