#include<fstream>
using namespace std;
ifstream f("iso.in");
ofstream g("iso.out");
int main()
{
    int x,m,i;
    f>>x>>m;
    if(m>x)
        g<<"0";
    else
        {
            for(i=x;i>=m;i--)
            {
                if(x%i==0)
                    g<<i<<" ";
            }
        }
        f.close();g.close();
        return 0;
}
