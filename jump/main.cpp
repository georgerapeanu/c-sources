#include <fstream>
using namespace std;
ifstream f("jump.in");
ofstream g("jump.out");
int a=1,b=2,c=4,N,i,tmp;
int main()
{
    f>>N;
    if(N==1)
        g<<1;
    else if(N==2)
        g<<2;
    else if(N==3)
        g<<4;
    else
    {
        for(i=4;i<=N;i++)
        {
            tmp=c;
            c=(a+b+c)%666013;
            a=b;
            b=tmp;
        }
        g<<c;
    }
    f.close();
    g.close();
    return 0;
}
