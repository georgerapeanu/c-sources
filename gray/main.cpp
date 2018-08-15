#include <fstream>
#include <cmath>
using namespace std;
ifstream f("gray.in");
ofstream g("gray.out");
bool a;
short n,i,nr1;
unsigned long long st,fn,b,nr;
int main()
{
    f>>n;
    fn=pow(2,n)-1;
    for(i=1;i<=n;i++)
    {
        f>>a;
        if(a==1)
            {
                if(nr1%2==1)
                {
                    fn=(st+fn)/2;
                }
                else
                {
                    st=(st+fn+1)/2;
                }
                nr1++;
            }
        else
            {
                if(nr1%2==0)
                {
                    fn=(st+fn)/2;
                }
                else
                {
                    st=(st+fn+1)/2;
                }
            }
    }
    b+=st;
    fn=pow(2,n)-1;nr1=0;
    st=0;
     for(i=1;i<=n;i++)
    {
        f>>a;
        if(a==1)
            {
                if(nr1%2==1)
                {
                    fn=(st+fn)/2;
                }
                else
                {
                    st=(st+fn+1)/2;
                }
                nr1++;
            }
        else
            {
                if(nr1%2==0)
                {
                    fn=(st+fn)/2;
                }
                else
                {
                    st=(st+fn+1)/2;
                }
            }
    }
    b+=st;
    nr=pow(2,n-1);
    while(b>1)
    {
       if(b>=nr)
       {g<<1<<" ";b=nr*2-1-b;}
       else
       g<<0<<" ";
       nr=nr/2;
    }
    g<<b;
    f.close();g.close();
    return 0;
}
