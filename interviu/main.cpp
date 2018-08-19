#include <fstream>
using namespace std;
ifstream f("interviu.in");
ofstream g("interviu.out");
int v[100],i,j,n,gasit,a;
int main()
{
    f>>n;
    for(i=0;i<n;i++)
    {
        f>>v[i];
        if(i>2)
        {
            for(j=0;j<i;j++)
            {
                if(v[i]<=v[j])
                break;
            }
            if(j==i)
            {
                gasit=1;
            }
        }
        if(gasit==1)
            {
                a=i+1;
                break;
            }
    }
    if(gasit==0)
        g<<n;
    else
        g<<a;
    return 0;
}
