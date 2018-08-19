#include<fstream>
using namespace std;
ifstream f("sirdesc.in");
ofstream g("sirdesc.out");
int n,k,d,m,im,nm,i,j;
int main()
{
    f>>n>>k>>d>>m>>nm;
    for(i=1;i<=n-d;i++)
    {
        for(j=i+d;j<=n;j++)
        {
            im++;
            if(im==nm)
            {
                f>>nm;
                g<<j<<" "<<i<<"\n";
            }
            if(im>nm)
            {
                break;
            }
        }
    }
    f.close();g.close();
    return 0;
}
