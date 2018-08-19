#include <fstream>
using namespace std;
ifstream f("centrale.in");
ofstream g("centrale.out");
char c,nr;
bool adev;
int nra,i,n;
int main()
{
    f>>n;f.get(c);
    for(i=1;i<=n;i++)
    {
        f.get(c);
        f.get(c);
        nr=c;
        adev=1;
        while(c>='0'&&c<='9')
        {
            f.get(c);
            if(c!=nr&&c>='0'&&c<='9')
            {
                f.get(c);
                if(c>='0'&&c<='9')
                {
                    f.putback(c);
                    adev=0;
                }
            }
        }
        nra+=adev==true ? 1:0;
    }
    g<<nra;
    f.close();
    g.close();
    return 0;
}
