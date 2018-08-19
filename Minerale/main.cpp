#include <fstream>
using namespace std;
ifstream f("minerale.in");
ofstream g("minerale.out");
bitset<30> dp[105][105];
map<string,char> M;
int r,m;
char c;
string a;
int main()
{
    f>>r>>m;
    for(int i=1;i<=r;i++)
    {
        f>>c>>a;
        M[a]=c;
    }
    return 0;
}
