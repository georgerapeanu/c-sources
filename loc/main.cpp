#include <fstream>
using namespace std;
ifstream f("loc.in");
ofstream g("loc.out");
int n,v[1001],i,j,k,hold,hold2,nr;
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>v[i];
    }
    for(i=1;i<=n;i++)
    {
        if(v[i]!=i)
        {
            nr++;
            hold=v[i];
            v[i]=0;
            while(v[hold]!=hold)
            {
                hold2=v[hold];
                v[hold]=hold;
                if(hold)
                hold=hold2;
            }
        }
    }
    g<<nr;
    return 0;
}
