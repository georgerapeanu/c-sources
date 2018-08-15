//rapeanu george alexandru
#include<fstream>
using namespace std;
ifstream f("fatfrumos.in");
ofstream g("fatfrumos.out");
int main()
{
    int n,m,p=0,i,j=1;
    f>>n;
    f>>m;
    for(i=1;i<=m;i++)
    {
        n=n*j;
        j++;
        p=p+n;
    }
    g<<p;
    g.close();f.close();
    return 0;
}
