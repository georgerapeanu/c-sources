#include<fstream>
using namespace std;
ifstream f("alo.in");
ofstream g("alo.out");
int main()
{
    int c,v,n,uc,i,d;
    f>>c>>v;
    for(i=1;i<=v;i++)
    {
        f>>n>>d;
        uc=n%10;
        if(uc==9)
        {
            c+=0;
        }
        else
        {
            if(n/10000==1)
            {
                c=c-2*d;
            }
            else
                c=c+d;
        }
    }
    g<<c;
    f.close();g.close();
    return 0;
}
