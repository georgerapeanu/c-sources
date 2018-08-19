#include<fstream>
using namespace std;
ifstream f("fazanr.in");
ofstream g("fazanr.out");
int main()
{
    int i,n,uc,a,ne=0,b;
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>a;
        if(i==1)
        {
            uc=a%10;
        }
        else
        {
            b=a;
            while(b>=10)
            {
                b=b/10;
            }
            if(b!=uc)
            {
               ne++;
            }
            uc=a%10;
        }
    }
    g<<ne;
}
