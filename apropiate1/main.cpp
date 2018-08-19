#include <fstream>
using namespace std;
ifstream f("apropiate1.in");
ofstream g("apropiate1.out");
long long x,y,a,i,j,n,distx,disty;
short c;
int ifprim(long long nr)
{
    long long l;
    for(l=2;l<=nr/2;l++)
    if(nr%l==0)
    return 0;
    return 1;
}
int main()
{
    f>>n>>c;
    for(i=1;i<=n;i++)
    {
        f>>a;
        if(ifprim(a)==1)
        g<<a<<" ";
        else
        {
            x=y=a;
            while(ifprim(x)==0)
            x--;
            while(ifprim(y)==0)
            y++;
            distx=a-x;
            disty=y-a;
            if(distx>disty)
            g<<y<<" ";
            else if(distx<disty)
            g<<x<<" ";
            else
            {
                if(c==1)
                g<<x<<" ";
                else
                g<<y<<" ";
            }
        }
    }
    f.close();g.close();
    return 0;
}
