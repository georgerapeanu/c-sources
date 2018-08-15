#include <fstream>
using namespace std;
ifstream f("albine2.in");
ofstream g("albine2.out");
long n,m,x,y,e,c,i,b,v,o;
int main()
{
    f>>n>>m;
    x=y=n;
    for(i=1;i<=m;i++)
    {
        f>>b;
        if(b==0)
            {
                if(v>=0)
                    x--;
                else
                    x++;
                v++;
            }
        else if(b==1)
            {
                if(o>=0)
                  y--;
                else
                  y++;
                o++;
            }
        else if(b==2)
           {
                if(v<=0)
                    x--;
                else
                    x++;
                v--;
           }
        else
            {
                if(o<=0)
                    y--;
                else
                    y++;
                o--;
            }
            e=n*n-(x*y);
            c=c+e;
    }
    g<<c;
    f.close();g.close();
    return 0;
}
