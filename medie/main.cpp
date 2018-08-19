#include <fstream>
using namespace std;
ifstream f("medie.in");
ofstream g("medie.out");
long n,c,medie,a,i,v[101],m,j;
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>c;
        medie=0;m=0;
        for(j=1;j<=c;j++)
        {
            f>>v[j];
            medie+=v[j];
        }
        medie=medie/c;
        for(j=1;j<=c;j++)
        {
            if(v[j]>=medie)
            m++;
        }
        g<<m<<"/"<<c<<"\n";
    }
    f.close();g.close();
    return 0;
}
